#include "stdafx.h"
#include "PEView.h"
namespace PEView
{
	// !δ���
	// ����PE��������ʹ�����ӣ��п���������
	// �����������ô�������ʱ������Win10Ч�����������У���֪���������汾ϵͳ�ϻ᲻��󵽱���

	// ���ȱ�
	// TODO:��Ҫ����CFF���ƵĹ��ܣ���д��δ�����[=]���������[X]��δд��[ ]
	// [=] ������ö��ֵ������Ҫ��ʾ��ʾ,Meaning����Ҫ����һЩ����������������Щ�����õĽṹδд����
	//		[=] pe info - ȱidentifier�������ģ��д���ٲ���
	//		[X] Dos Header
	//		[X] Nt Header
	//		[X] File Header
	//		[X] Optional Header
	//		[X] Data Directories
	//		[=] Section Headers - ȱ16���Ʊ༭����
	//		[=] Import Directory
	//		[=] Resource Directory
	// [ ] �༭(����pe�ṹ����Դ����ӽṹ���ƶ����벢�ض�λ��) - �п���д
	// [=] Address Converter - �������У��޽���
	// [ ] Dependency Walker - ��ͨ����д�����޸Ķ������޽���
	// [ ] Hex Editer
	// [ ] Identifier
	// [ ] Import Adder
	// [ ] Quick Disassembler - д��һ���п���д����Ҫд��̫���ˣ�
	// [ ] Rebuilder
	// [ ] Resource Editor
	// [X] ֧�ֲ��(���в��+peid���,������Ϊ���йܳ���,peid���������ȫ����,���в���������ٲ��䣩

	// TODO:��Ҫ����PEID���ƵĹ��ܣ�����Ĳ��䣩
	// [ ] CaveFinder
	// [ ] Entropy
	// [ ] ����scan

	// ������Ҫ�޸�һ�����ݵ���ʾ��ʽ
	PEView::PEView(void)
	{
		InitializeComponent();
		draw = gcnew TreeNodeDrawer(treeMenu, gcnew TreeNodeStyle_Blue());
		treeMenu->Visible = false;
		splitContainer1->Panel2->Visible = false;

		menuActions = gcnew Dictionary<TreeNode^, System::Action^>();
		defaultMenuactions = gcnew Dictionary<TreeNode^, System::Action^>();
		exMenuActions = gcnew Dictionary<TreeNode^, System::Action^>();
		isDefaultMenuInit = false;
		isExMenuInit = false;

		peFile = gcnew PeFile();
		peFile->Closed += gcnew System::Action(this, &PEView::PEView::OnClosed);

		infoList = gcnew InfoListControl();

		(gcnew Threading::Tasks::Task(gcnew Action(this, &PEView::LoadPlugin)))->Start();
	}

	void PEView::LoadPlugin()
	{
		pluginMenu = gcnew PluginMenuManager(pluginToolStripMenuItem);
	}
	System::Void PEView::aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		auto title = marshal_as<std::wstring>(this->Text);

		ShellAboutW((HWND)this->Handle.ToPointer(), (LPCWSTR)title.c_str(), L"���������", NULL);

	}
	void PEView::CloseFile()
	{
		peFile->CloseFile();
		pluginMenu->OnCloseFile();
	}
	System::Void PEView::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				peFile->OpenFile(openFileDialog->FileName, openFileDialog->ReadOnlyChecked);
				pluginMenu->OnOpenFIle(this->Handle, peFile->ExePath, peFile->ExePtr, peFile->MapSize, openFileDialog->ReadOnlyChecked);
				// ֪ͨ���½���
				InitUI();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message, "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
	}
	System::Void PEView::treeMenu_DrawNode(System::Object ^ sender, System::Windows::Forms::DrawTreeNodeEventArgs ^ e)
	{
		draw->Draw(e);
	}


	void PEView::InitUI()
	{
		InitTreeView();
		treeMenu->Visible = true;
		splitContainer1->Panel2->Visible = true;
		treeNode_Exe->Text = System::IO::Path::GetFileName(peFile->ExePath);

		// ����pe�Ľṹ������չ�˵�
		/////////////////////////////////
		treeMenu->SelectedNode = treeNode_Exe;
	}

	void PEView::InitTreeView()
	{
		treeMenu->Nodes->Clear();
		menuActions->Clear();

		// ����̶��Ĳ˵��ڵ���
		if (!isDefaultMenuInit)
		{
			isDefaultMenuInit = true;
			InitDefaultMenu();

		}
		// �̶��˵�ȫ���
		this->treeMenu->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode_Exe });
		// ��Ӳ˵�����
		for each (auto var in defaultMenuactions)
		{
			menuActions->Add(var.Key, var.Value);
		}

		// ������չ�˵��Ľڵ���
		if (!isExMenuInit)
		{
			isExMenuInit = true;
			InitExMenu();
		}

		// ��չ�˵�ѡ�������
		if (peDecoder->GetExport()->IsExist())
		{
			AddExMenu(treeNode_ExportDirectories);
		}
		if (peDecoder->GetImport()->IsExist())
		{
			AddExMenu(treeNode_ImportDirectories);
		}
		if (peDecoder->GetResource()->IsExist())
		{
			AddExMenu(treeNode_ResourceDirectory);
		}
		if (peDecoder->GetReloc()->IsExist())
		{
			AddExMenu(treeNode_RelocationDirectory);
		}
		if (peDecoder->GetDebug()->IsExist())
		{
			AddExMenu(treeNode_DebugDirectory);
		}
		if (peDecoder->GetTls()->IsExist())
		{
			AddExMenu(treeNode_TLSDirectory);
		}
		if (peDecoder->GetArchitecture()->IsExist())
		{
			//
		}
		if (peDecoder->GetBoundImport()->IsExist())
		{
			//
		}
		if (peDecoder->GetComDescriptor()->IsExist())
		{
			//
		}
		if (peDecoder->GetIat()->IsExist())
		{
			//
		}
		if (peDecoder->GetDelayImport()->IsExist())
		{
			//
		}
		if (peDecoder->GetLoadConfig()->IsExist())
		{
			//
		}
		if (peDecoder->GetSecurity()->IsExist())
		{
			//
		}
		if (peDecoder->GetGlobalptr()->IsExist())
		{
			//
		}
		if (peDecoder->GetException()->IsExist())
		{
			//
		}
		///////////////////////////////////////////

		this->treeMenu->ExpandAll();
	}
	void PEView::InitDefaultMenu()
	{
		treeNode_DosHeader = (gcnew System::Windows::Forms::TreeNode(L"Dos Header"));
		treeNode_FileHeader = (gcnew System::Windows::Forms::TreeNode(L"File Header"));
		treeNode_DataDirectories = (gcnew System::Windows::Forms::TreeNode(L"Data Directories"));
		treeNode_OptionalHeader = (gcnew System::Windows::Forms::TreeNode(L"Optional Header", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode_DataDirectories }));
		treeNode_NtHeader = (gcnew System::Windows::Forms::TreeNode(L"Nt Header", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) { treeNode_FileHeader, treeNode_OptionalHeader }));
		treeNode_SectionHeader = (gcnew System::Windows::Forms::TreeNode(L"Section Headers"));
		treeNode_Exe = (gcnew System::Windows::Forms::TreeNode(L"Exe", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) { treeNode_DosHeader, treeNode_NtHeader, treeNode_SectionHeader }));
		treeNode_DosHeader->Name = str_DosHeader;
		treeNode_FileHeader->Name = str_FileHeader;
		treeNode_DataDirectories->Name = str_DataDirectories;
		treeNode_OptionalHeader->Name = str_OptionalHeader;
		treeNode_NtHeader->Name = str_NtHeader;
		treeNode_SectionHeader->Name = str_SectionHeader;
		treeNode_Exe->Name = str_Exe;


		defaultMenuactions->Add(treeNode_DosHeader, gcnew System::Action(this, &PEView::OnDosHeaderClick));
		defaultMenuactions->Add(treeNode_FileHeader, gcnew System::Action(this, &PEView::OnFileHeaderClick));
		defaultMenuactions->Add(treeNode_DataDirectories, gcnew System::Action(this, &PEView::OnDataDirectoriesClick));
		defaultMenuactions->Add(treeNode_OptionalHeader, gcnew System::Action(this, &PEView::OnOptionalHeaderClick));
		defaultMenuactions->Add(treeNode_NtHeader, gcnew System::Action(this, &PEView::OnNtHeaderClick));
		defaultMenuactions->Add(treeNode_SectionHeader, gcnew System::Action(this, &PEView::OnSectionHeaderClick));
		defaultMenuactions->Add(treeNode_Exe, gcnew System::Action(this, &PEView::OnExeClick));
	}

	void PEView::InitExMenu()
	{
		treeNode_ExportDirectories = (gcnew System::Windows::Forms::TreeNode(L"Export Directories"));
		treeNode_ImportDirectories = (gcnew System::Windows::Forms::TreeNode(L"Import Directories"));
		treeNode_ResourceDirectory = (gcnew System::Windows::Forms::TreeNode(L"Resource Directory"));
		treeNode_RelocationDirectory = (gcnew System::Windows::Forms::TreeNode(L"Relocation Directory"));
		treeNode_DebugDirectory = (gcnew System::Windows::Forms::TreeNode(L"Debug Directory"));
		treeNode_TLSDirectory = (gcnew System::Windows::Forms::TreeNode(L"TLS Directory"));

		treeNode_ExportDirectories->Name = str_ExportDirectories;
		treeNode_ImportDirectories->Name = str_ImportDirectories;
		treeNode_ResourceDirectory->Name = str_ResourceDirectory;
		treeNode_RelocationDirectory->Name = str_RelocationDirectory;
		treeNode_DebugDirectory->Name = str_DebugDirectory;
		treeNode_TLSDirectory->Name = str_TLSDirectory;

		exMenuActions->Add(treeNode_ExportDirectories, gcnew System::Action(this, &PEView::ExportDirectoriesClick));
		exMenuActions->Add(treeNode_ImportDirectories, gcnew System::Action(this, &PEView::ImportDirectoriesClick));
		exMenuActions->Add(treeNode_ResourceDirectory, gcnew System::Action(this, &PEView::ResourceDirectoryClick));
		exMenuActions->Add(treeNode_RelocationDirectory, gcnew System::Action(this, &PEView::RelocationDirectoryClick));
		exMenuActions->Add(treeNode_DebugDirectory, gcnew System::Action(this, &PEView::DebugDirectoryClick));
		exMenuActions->Add(treeNode_TLSDirectory, gcnew System::Action(this, &PEView::TLSDirectoryClick));
	}
	void PEView::AddExMenu(TreeNode^ node)
	{
		assert(node != nullptr);
		menuActions->Add(node, exMenuActions[node]);
		this->treeMenu->Nodes->Add(node);
	}
	System::Void PEView::treeMenu_BeforeSelect(System::Object ^ sender, System::Windows::Forms::TreeViewCancelEventArgs ^ e)
	{
		(gcnew Threading::Tasks::Task(menuActions[e->Node]))->Start();
	}
	System::Void PEView::treeMenu_AfterSelect(System::Object ^ sender, System::Windows::Forms::TreeViewEventArgs ^ e)
	{
		//this->Text = "PE View - " + e->Node->Text;
	}

	System::Void PEView::OnDosHeaderClick()
	{
		AddInfoListControl(peFile->DosHeader);
	}
	System::Void PEView::OnFileHeaderClick()
	{
		AddInfoListControl(peFile->FileHeader);
	}
	System::Void PEView::OnDataDirectoriesClick()
	{
		AddInfoListControl(peFile->DataDirectories);
	}
	System::Void PEView::OnOptionalHeaderClick()
	{
		AddInfoListControl(peFile->OptionalHeader);
	}
	System::Void PEView::OnNtHeaderClick()
	{
		AddInfoListControl(peFile->NtHeader);
	}
	System::Void PEView::OnSectionHeaderClick()
	{
		AddInfoListControl(peFile->Section, gcnew Action<DataGridView^>(this, &PEView::OnSectionRowSelectionChanged));
	}

	System::Void PEView::OnSectionRowSelectionChanged(DataGridView^ sender)
	{
		assert(sender != nullptr);
		if (sender->SelectedRows->Count > 0 && sender->SelectedRows[0]->Index == 0)
		{
			sender->SelectedRows[0]->Selected = false;
			return;
		}
		sender->InvalidateRow(0);
	}


	void PEView::AddInfoListControl(List<String^>^ cols, int rowCount, Func<DataGridView^, int, int, String^>^ getCell, Action<DataGridView^>^ selectionChanged)
	{
		assert(cols!=nullptr && getCell != nullptr);
		bool needAdd = true;
		if (splitContainer1->Panel2->Controls->Count > 0)
		{
			if (splitContainer1->Panel2->Controls[0] != infoList)
			{
				splitContainer1->Panel2->Controls->Clear();
			}
			else
			{
				needAdd = false;
			}
		}

		infoList->Clear();
		infoList->AddCols(cols);

		if (lastCellValueNeeded)
		{
			infoList->CellValueNeeded -= lastCellValueNeeded;
		}
		infoList->CellValueNeeded += getCell;
		lastCellValueNeeded = getCell;

		if (lastSelectionChanged)
		{
			infoList->SelectionChanged -= lastSelectionChanged;
		}
		infoList->SelectionChanged += selectionChanged;
		lastSelectionChanged = selectionChanged;


		infoList->RowCount = rowCount;
		if (needAdd)
		{
			splitContainer1->Panel2->Controls->Add(infoList);
		}


	}
	void PEView::AddInfoListControl(IPeDataReader^ reader)
	{
		
		AddInfoListControl(reader, nullptr);
	}
	void PEView::AddInfoListControl(IPeDataReader^ reader, Action<DataGridView^>^ selectionChanged)
	{
		assert(reader != nullptr);
		splitContainer1->Invoke(gcnew Action<List<String^>^, int, Func<DataGridView^, int, int, String^>^, Action<DataGridView^>^>(this, &PEView::AddInfoListControl),
			reader->GetCols(),
			reader->GetCount(),
			gcnew Func<DataGridView^, int, int, String^>(reader, &IPeDataReader::GetCell),
			selectionChanged
			);
	}
	System::Void PEView::OnExeClick()
	{
		AddInfoListControl(peFile->ExeInfo);
	}

	System::Void PEView::ExportDirectoriesClick()
	{}

	System::Void PEView::ImportDirectoriesClick()
	{}

	System::Void PEView::ResourceDirectoryClick()
	{}

	System::Void PEView::RelocationDirectoryClick()
	{}

	System::Void PEView::DebugDirectoryClick()
	{}

	System::Void PEView::TLSDirectoryClick()
	{}
	void PEView::OnClosed()
	{
		treeMenu->Visible = false;
		splitContainer1->Panel2->Visible = false;
		treeMenu->Nodes->Clear();
		menuActions->Clear();
	}
	inline System::Void PEView::closeToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) 
	{
		CloseFile();
	}
}


