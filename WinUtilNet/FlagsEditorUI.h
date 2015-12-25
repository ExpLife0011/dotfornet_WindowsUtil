#pragma once

namespace NAMESPACE {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms::Design;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// CharacteristicsEditorUI ժҪ
	/// </summary>
	generic<typename T> where T:Enum
		public ref class FlagsEditorUI : public System::Windows::Forms::UserControl
	{
		T value;
		DialogResult result;
		IWindowsFormsEditorService^ svc;
	public:
		FlagsEditorUI(T value, IWindowsFormsEditorService^ svc) :value(value), svc(svc)
		{
			InitializeComponent();

			// ��ӿؼ�

			auto options = Enum::GetValues(T::typeid);
			auto valueInt = Convert::ToInt32(value); 
			this->SuspendLayout();
			for each (auto var in options)
			{
				auto tmpCheckBox = gcnew CheckBox();
				auto varInt = Convert::ToInt32(var);
				tmpCheckBox->Text =String::Format("{0} ({1:X4})", Enum::GetName(T::typeid, var),varInt);// peͷö�ٴ�ΪWORD����
				tmpCheckBox->Tag = var;
				tmpCheckBox->AutoSize = true;
				
				if ((valueInt & varInt) == varInt)
				{
					// ��ѡ��
					tmpCheckBox->Checked = true;
				}
				tmpCheckBox->CheckedChanged += gcnew System::EventHandler(this, &NAMESPACE::FlagsEditorUI<T>::OnCheckedChanged);
				flowLayoutPanel1->Controls->Add(tmpCheckBox);
			}
			this->ResumeLayout(false);
		}
		property T Value
		{
			T get()
			{
				return value;
			}
		}

		property DialogResult Result
		{
			DialogResult get()
			{
				return result;
			}
		}
	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~FlagsEditorUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	protected:

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->AutoSize = true;
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(303, 325);
			this->flowLayoutPanel1->TabIndex = 0;
			this->flowLayoutPanel1->WrapContents = false;
			// 
			// button1
			// 
			this->button1->AutoSize = true;
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(225, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ȷ��";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FlagsEditorUI::button1_Click);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->flowLayoutPanel1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->button1);
			this->splitContainer1->Size = System::Drawing::Size(303, 363);
			this->splitContainer1->SplitterDistance = 325;
			this->splitContainer1->TabIndex = 1;
			// 
			// CharacteristicsEditorUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->Controls->Add(this->splitContainer1);
			this->Name = L"FlagsEditorUI";
			this->Size = System::Drawing::Size(303, 363);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	private:
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			result = DialogResult::OK;
			svc->CloseDropDown();
		}
		void OnCheckedChanged(System::Object ^sender, System::EventArgs ^e)
		{
			auto checkBox = (CheckBox^)sender;
			auto valueName = checkBox->Text;
			auto newValue = Convert::ToInt32(checkBox->Tag);
			auto valueInt = Convert::ToInt32(value);
			if (checkBox->Checked)
			{
				value = (T)Enum::Parse(T::typeid, Convert::ToString(newValue | valueInt));
			}
			else
			{
				value = (T)Enum::Parse(T::typeid, Convert::ToString(~newValue & valueInt));
			}
		}
	};
}

