#pragma once

#include "input.h"

#include "config.h"
#include "convert.h"
#include "header.h"
#include "debug.h"
#include "handler.h"
#include <cassert>
#include <chrono>
#include <thread>

namespace EscoCp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Threading;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		HWND hWnd;

		Handler* hHandler = nullptr;

		std::map<int, bool>* keys;
		Config* cfg;
		Profile* currentProfile;

		std::vector<Profile>* profile;

		int force, delay;

		bool captureKey = false;

	private: System::Windows::Forms::CheckBox^ chkOntop;
	private: System::Windows::Forms::TextBox^ btnActivate;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ btnVanish;
	private: System::Windows::Forms::Label^ label5;




	public:
		int SelectedIndex = -1;

	public:
		MyForm(void)
		{
			this->InitializeComponent();

			hWnd = static_cast<HWND>(this->Handle.ToPointer());
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (keys) {
				delete keys;
			}
			if (cfg) {
				delete cfg;
			}
			if (components) {
				delete components;
			}
			return;
		}
	private: System::Windows::Forms::Label^ btnAddProfile;
	protected:

	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::ListBox^ listProfiles;
	private: System::Windows::Forms::TextBox^ inpProfile;




	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::Button^ btnAssign;


	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Button^ btnRestore;


	private: System::Windows::Forms::GroupBox^ groupBox2;














	private: System::Windows::Forms::Label^ txtActivatebtn;


	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::NumericUpDown^ inpRecoilStanding;
	private: System::Windows::Forms::NumericUpDown^ inpDelayStanding;
	private: System::Windows::Forms::NumericUpDown^ inpDelayCrouch;
	private: System::Windows::Forms::NumericUpDown^ inpRecoilCrouch;
	private: System::Windows::Forms::NumericUpDown^ inpRecoilProne;
	private: System::Windows::Forms::NumericUpDown^ inpDelayProne;


	private: System::Windows::Forms::Label^ outMessage;
	private: System::Windows::Forms::Label^ label15;



	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->btnAddProfile = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->btnRestore = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->listProfiles = (gcnew System::Windows::Forms::ListBox());
			this->inpProfile = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnVanish = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btnActivate = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->inpRecoilStanding = (gcnew System::Windows::Forms::NumericUpDown());
			this->inpDelayStanding = (gcnew System::Windows::Forms::NumericUpDown());
			this->inpDelayCrouch = (gcnew System::Windows::Forms::NumericUpDown());
			this->inpRecoilCrouch = (gcnew System::Windows::Forms::NumericUpDown());
			this->inpRecoilProne = (gcnew System::Windows::Forms::NumericUpDown());
			this->inpDelayProne = (gcnew System::Windows::Forms::NumericUpDown());
			this->outMessage = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->chkOntop = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilStanding))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayStanding))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayCrouch))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilCrouch))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilProne))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayProne))->BeginInit();
			this->SuspendLayout();
			// 
			// btnAddProfile
			// 
			this->btnAddProfile->AutoSize = true;
			this->btnAddProfile->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnAddProfile->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAddProfile->ForeColor = System::Drawing::SystemColors::Highlight;
			this->btnAddProfile->Location = System::Drawing::Point(6, -2);
			this->btnAddProfile->Name = L"btnAddProfile";
			this->btnAddProfile->Size = System::Drawing::Size(87, 17);
			this->btnAddProfile->TabIndex = 2;
			this->btnAddProfile->Text = L"+ Add profile";
			this->btnAddProfile->Click += gcnew System::EventHandler(this, &MyForm::btnAddProfile_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->btnRestore);
			this->groupBox4->Controls->Add(this->btnSave);
			this->groupBox4->Controls->Add(this->btnAddProfile);
			this->groupBox4->Controls->Add(this->listProfiles);
			this->groupBox4->Location = System::Drawing::Point(12, 12);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(155, 246);
			this->groupBox4->TabIndex = 14;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L" ";
			// 
			// btnRestore
			// 
			this->btnRestore->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnRestore->Location = System::Drawing::Point(79, 217);
			this->btnRestore->Name = L"btnRestore";
			this->btnRestore->Size = System::Drawing::Size(70, 23);
			this->btnRestore->TabIndex = 24;
			this->btnRestore->Text = L"Restore all";
			this->btnRestore->UseVisualStyleBackColor = true;
			this->btnRestore->Click += gcnew System::EventHandler(this, &MyForm::btnRestore_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(6, 217);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(70, 23);
			this->btnSave->TabIndex = 23;
			this->btnSave->Text = L"Save all";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &MyForm::btnSave_Click);
			// 
			// listProfiles
			// 
			this->listProfiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listProfiles->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listProfiles->ForeColor = System::Drawing::Color::Gray;
			this->listProfiles->FormattingEnabled = true;
			this->listProfiles->IntegralHeight = false;
			this->listProfiles->Location = System::Drawing::Point(6, 22);
			this->listProfiles->Name = L"listProfiles";
			this->listProfiles->Size = System::Drawing::Size(143, 189);
			this->listProfiles->TabIndex = 1;
			this->listProfiles->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listProfiles_SelectedIndexChanged);
			this->listProfiles->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::listProfiles_MDown);
			// 
			// inpProfile
			// 
			this->inpProfile->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->inpProfile->Location = System::Drawing::Point(114, 16);
			this->inpProfile->Name = L"inpProfile";
			this->inpProfile->Size = System::Drawing::Size(194, 20);
			this->inpProfile->TabIndex = 16;
			this->inpProfile->TextChanged += gcnew System::EventHandler(this, &MyForm::inpProfile_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->btnActivate);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->inpProfile);
			this->groupBox1->Location = System::Drawing::Point(173, 42);
			this->groupBox1->Margin = System::Windows::Forms::Padding(0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(0);
			this->groupBox1->Size = System::Drawing::Size(321, 81);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			// 
			// btnVanish
			// 
			this->btnVanish->Cursor = System::Windows::Forms::Cursors::Default;
			this->btnVanish->ForeColor = System::Drawing::Color::Gray;
			this->btnVanish->Location = System::Drawing::Point(287, 19);
			this->btnVanish->Name = L"btnVanish";
			this->btnVanish->ReadOnly = true;
			this->btnVanish->Size = System::Drawing::Size(92, 20);
			this->btnVanish->TabIndex = 24;
			this->btnVanish->Click += gcnew System::EventHandler(this, &MyForm::btnVanish_click);
			this->btnVanish->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::btnVanish_KeyDown);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(189, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(73, 13);
			this->label5->TabIndex = 23;
			this->label5->Text = L"Vanish Button";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(16, 16);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(67, 13);
			this->label12->TabIndex = 22;
			this->label12->Text = L"Profile Name";
			// 
			// btnActivate
			// 
			this->btnActivate->Cursor = System::Windows::Forms::Cursors::Default;
			this->btnActivate->ForeColor = System::Drawing::Color::Gray;
			this->btnActivate->Location = System::Drawing::Point(114, 45);
			this->btnActivate->Name = L"btnActivate";
			this->btnActivate->ReadOnly = true;
			this->btnActivate->Size = System::Drawing::Size(194, 20);
			this->btnActivate->TabIndex = 21;
			this->btnActivate->Click += gcnew System::EventHandler(this, &MyForm::btnActivate_Click);
			this->btnActivate->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::btnActivate_KeyDown);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(16, 45);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(80, 13);
			this->label7->TabIndex = 20;
			this->label7->Text = L"Activate Button";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->AutoSize = true;
			this->groupBox2->Controls->Add(this->tableLayoutPanel1);
			this->groupBox2->Location = System::Drawing::Point(173, 123);
			this->groupBox2->Margin = System::Windows::Forms::Padding(0);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(0);
			this->groupBox2->Size = System::Drawing::Size(321, 135);
			this->groupBox2->TabIndex = 15;
			this->groupBox2->TabStop = false;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->Controls->Add(this->label9, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->label6, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->label2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->inpRecoilStanding, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->inpDelayStanding, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->inpDelayCrouch, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->inpRecoilCrouch, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->inpRecoilProne, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->inpDelayProne, 1, 3);
			this->tableLayoutPanel1->Location = System::Drawing::Point(10, 13);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(305, 104);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label9->Location = System::Drawing::Point(3, 78);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(95, 26);
			this->label9->TabIndex = 11;
			this->label9->Text = L"Prone";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label6->Location = System::Drawing::Point(3, 52);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(95, 26);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Crouch";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label4->Location = System::Drawing::Point(3, 26);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(95, 26);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Standing";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(205, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(97, 26);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Force";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(104, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(95, 26);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Delay(ms)";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 26);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Stance";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// inpRecoilStanding
			// 
			this->inpRecoilStanding->Location = System::Drawing::Point(205, 29);
			this->inpRecoilStanding->Name = L"inpRecoilStanding";
			this->inpRecoilStanding->Size = System::Drawing::Size(93, 20);
			this->inpRecoilStanding->TabIndex = 0;
			this->inpRecoilStanding->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpRecoilStanding_ValueChanged);
			// 
			// inpDelayStanding
			// 
			this->inpDelayStanding->Location = System::Drawing::Point(104, 29);
			this->inpDelayStanding->Name = L"inpDelayStanding";
			this->inpDelayStanding->Size = System::Drawing::Size(92, 20);
			this->inpDelayStanding->TabIndex = 1;
			this->inpDelayStanding->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpDelayStanding_ValueChanged);
			// 
			// inpDelayCrouch
			// 
			this->inpDelayCrouch->Location = System::Drawing::Point(104, 55);
			this->inpDelayCrouch->Name = L"inpDelayCrouch";
			this->inpDelayCrouch->Size = System::Drawing::Size(92, 20);
			this->inpDelayCrouch->TabIndex = 2;
			this->inpDelayCrouch->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpDelayCrouch_ValueChanged);
			// 
			// inpRecoilCrouch
			// 
			this->inpRecoilCrouch->Location = System::Drawing::Point(205, 55);
			this->inpRecoilCrouch->Name = L"inpRecoilCrouch";
			this->inpRecoilCrouch->Size = System::Drawing::Size(93, 20);
			this->inpRecoilCrouch->TabIndex = 3;
			this->inpRecoilCrouch->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpRecoilCrouch_ValueChanged);
			// 
			// inpRecoilProne
			// 
			this->inpRecoilProne->Location = System::Drawing::Point(205, 81);
			this->inpRecoilProne->Name = L"inpRecoilProne";
			this->inpRecoilProne->Size = System::Drawing::Size(93, 20);
			this->inpRecoilProne->TabIndex = 5;
			this->inpRecoilProne->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpRecoilProne_ValueChanged);
			// 
			// inpDelayProne
			// 
			this->inpDelayProne->Location = System::Drawing::Point(104, 81);
			this->inpDelayProne->Name = L"inpDelayProne";
			this->inpDelayProne->Size = System::Drawing::Size(92, 20);
			this->inpDelayProne->TabIndex = 4;
			this->inpDelayProne->ValueChanged += gcnew System::EventHandler(this, &MyForm::inpDelayProne_ValueChanged);
			// 
			// outMessage
			// 
			this->outMessage->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->outMessage->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->outMessage->Location = System::Drawing::Point(70, 261);
			this->outMessage->Name = L"outMessage";
			this->outMessage->Size = System::Drawing::Size(424, 18);
			this->outMessage->TabIndex = 17;
			this->outMessage->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label15
			// 
			this->label15->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label15->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label15->Location = System::Drawing::Point(12, 261);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(61, 18);
			this->label15->TabIndex = 18;
			this->label15->Text = L"Messages:";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// chkOntop
			// 
			this->chkOntop->AutoSize = true;
			this->chkOntop->Checked = true;
			this->chkOntop->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkOntop->Location = System::Drawing::Point(391, 21);
			this->chkOntop->Name = L"chkOntop";
			this->chkOntop->Size = System::Drawing::Size(58, 17);
			this->chkOntop->TabIndex = 19;
			this->chkOntop->Text = L"On top";
			this->chkOntop->UseVisualStyleBackColor = true;
			this->chkOntop->CheckedChanged += gcnew System::EventHandler(this, &MyForm::chkOntop_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(504, 288);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->btnVanish);
			this->Controls->Add(this->chkOntop);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->outMessage);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox4);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(520, 327);
			this->MinimumSize = System::Drawing::Size(520, 327);
			this->Name = L"MyForm";
			this->Text = L"EscoC";
			this->TopMost = true;
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilStanding))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayStanding))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayCrouch))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilCrouch))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpRecoilProne))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inpDelayProne))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		public: HWND getHwnd() {
			return this->hWnd;
		}
		public: void setHandler(Handler* h) {
			_S("Handler set");
			this->hHandler = h;
		}
		public: void setConfig(Config* c) {
			_S("Config set");
			this->cfg = c;

			if (cfg->read()) {
				writeMessage("Config read");
			}
			else {
				writeMessage("unable to read cfg, check for typos or delete file", true);
			}

			chkOntop->Checked = cfg->onTop;
			updateWindowPos();

			btnVanish->Text = getVanishKeyString();

			this->loadProfilesFromCfg();

			profile = new std::vector<Profile>;
			for (size_t p = 0; p < 1; p++)
				profile->push_back(Profile());
		}
		public: void SendOutputMessage(System::String^ msg) {
			this->outMessage->Text = msg;
		}
		// set names based on what profiles are in cfg
		public: void loadProfilesFromCfg() {
			listProfiles->Items->Clear();
			for (size_t i = 0; i < cfg->profileList.size(); i++)
			{
				const char* profname = cfg->profileList[i].name.c_str();
				System::String^ sprofname = System::String(profname).ToString();
				listProfiles->Items->Add(sprofname);
			}
		}
		public: void updateVisibility(bool visible) {
			if (visible) {
				ShowWindow(hWnd, SW_SHOW);
			}
			else
			{
				ShowWindow(hWnd, SW_HIDE);
			}
		}
		public: void updateWindowPos() {
			SetWindowPos(
				hWnd,
				(cfg->onTop ? HWND_TOPMOST : HWND_NOTOPMOST),
				cfg->x, cfg->y, 0, 0,
				SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_NOSIZE | SWP_NOMOVE
			);
		}
#pragma endregion
	private: System::Void btnAddProfile_Click(System::Object^ sender, System::EventArgs^ e) {
		Profile newProfile = Profile();
		newProfile.name = "New Profile";
		cfg->profileList.push_back(newProfile);
		loadProfilesFromCfg();
	}
	private: System::Void listProfiles_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		SelectedIndex = listProfiles->SelectedIndex;
		//_D("Selected index: " << SelectedIndex);
		if (SelectedIndex >= 0) {

			currentProfile = &cfg->profileList[SelectedIndex];

			inpDelayStanding->Value = currentProfile->delay[0];
			inpDelayCrouch->Value = currentProfile->delay[1];
			inpDelayProne->Value = currentProfile->delay[2];

			inpRecoilStanding->Value = currentProfile->recoil[0];
			inpRecoilCrouch->Value = currentProfile->recoil[1];
			inpRecoilProne->Value = currentProfile->recoil[2];

			btnActivate->Text = getOnKeyString();
			btnVanish->Text = getVanishKeyString();
			inpProfile->Text = System::String(currentProfile->name.c_str()).ToString();
		}
		listProfiles->SelectedIndex = SelectedIndex;
	}
	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cfg->write()) {
			writeMessage("Config saved");
		}
		else {
			writeMessage("Config was unable to save",true);
		}
	}
	private: System::Void btnRestore_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cfg->read()) {
			writeMessage("Config read");
		}
		else {
			writeMessage("unable to read cfg, check for typos or delete file", true);
		}
		loadProfilesFromCfg();
		listProfiles->SelectedIndex = -1;
	}
	private: System::Void chkOntop_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		cfg->onTop = chkOntop->Checked;
		updateWindowPos();
	}
	private: System::Void writeMessage(System::String^ message, bool error) {
		if (error) {
			outMessage->ForeColor = System::Drawing::Color::Red;
		}
		else {
			outMessage->ForeColor = System::Drawing::SystemColors::ControlLightLight;
		}
		outMessage->Text = message;
	}
	private: System::Void writeMessage(System::String^ message) {
		writeMessage(message, false);
	}
	private: System::Void btnActivate_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedIndex >= 0) {
			btnActivate->Text = "bind key (ESC to cancel)";
			this->ActiveControl = label1;
			//_D(currentProfile->name);
			hHandler->m_bCaptureKey = true;
			btnActivate->Focus();
		}
	}
	private: System::Void btnVanish_click(System::Object^ sender, System::EventArgs^ e) {
		btnVanish->Text = "bind key (ESC to cancel)";
		this->ActiveControl = label1;
		//_D(currentProfile->name);
		hHandler->m_bCaptureKey = true;
		btnVanish->Focus();
	}
	private: System::String^ getOnKeyString() {
		if (currentProfile->onkey == -1) {
			return gcnew String("NONE");
		}
		return gcnew String(vkToString(currentProfile->onkey).c_str());
	}
	private: System::String^ getVanishKeyString() {
		if (cfg->vanishkey == -1) {
			return gcnew String("NONE");
		}
		return gcnew String(vkToString(cfg->vanishkey).c_str());
	}
	private: System::Void btnActivate_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		DWORD key = (DWORD)e->KeyCode;
		if (hHandler->m_bCaptureKey) {
			hHandler->m_bCaptureKey = false;
			if (key != VK_ESCAPE) {
				currentProfile->onkey = key;
			}
			label1->Focus();
			btnActivate->Text = getOnKeyString();
		}

	}

	private: System::Void btnVanish_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		DWORD key = (DWORD)e->KeyCode;
		if (hHandler->m_bCaptureKey) {
			hHandler->m_bCaptureKey = false;
			if (key != VK_ESCAPE) {
				cfg->vanishkey = key;
			}
			label1->Focus();
			btnVanish->Text = getVanishKeyString();
		}
	}
	private: System::Void listProfiles_MDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right && SelectedIndex >= 0) {
			RECT pos;

			int wy = this->Top + 65;
			/*
			//this->
			//Point cLoc = this->PointToScreen(listProfiles->Location);
			//int ny = cLoc.Y;
			_D(this->PointToScreen(listProfiles->Location).Y << " " << this->Top << " " << wy);
			*/

			pos.top = this->Top + 65;
			pos.bottom = pos.top + listProfiles->ItemHeight * (SelectedIndex + 1);

			int py = Cursor->Position.Y;

			if (py <= pos.bottom && py >= pos.top) {//within listprofiles (top,left)
				String^ profName = gcnew String(currentProfile->name.c_str());

				// Initializes the variables to pass to the MessageBox.Show method.
				String^ message = "Really delete " + profName->ToUpper() + "?";
				String^ caption( "Are You Sure?" );
				MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				MessageBoxIcon icon = MessageBoxIcon::Question;

				Windows::Forms::DialogResult res = MessageBox::Show(message, caption, buttons, icon);
				if (res == Windows::Forms::DialogResult::Yes)
				{
					cfg->profileList.erase(cfg->profileList.begin() + SelectedIndex);
					loadProfilesFromCfg();
					SelectedIndex = -1;
					listProfiles->SelectedIndex = -1;
				}
			}
		}
	}
	public: int maxd(System::Decimal num, int min_) {
		return max((int)System::Decimal::Floor(num), min_);
	}
	private: System::Void inpDelayStanding_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->delay.at(STANDING) = maxd(  inpDelayStanding->Value , 1);
	}
	private: System::Void inpDelayCrouch_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->delay.at(CROUCH) = maxd(inpDelayCrouch->Value,1);
	}
	private: System::Void inpDelayProne_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->delay.at(PRONE) = maxd(inpDelayProne->Value,1);
	}
	private: System::Void inpRecoilStanding_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->recoil.at(STANDING) = maxd(inpRecoilStanding->Value,0);
	}
	private: System::Void inpRecoilCrouch_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->recoil.at(CROUCH) = maxd(inpRecoilCrouch->Value,0);
	}
	private: System::Void inpRecoilProne_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->recoil.at(PRONE) = maxd(inpRecoilProne->Value,0);
	}
	private: System::Void inpProfile_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentProfile == NULL)
			return;
		currentProfile->name = sysToStd(inpProfile->Text);
		loadProfilesFromCfg();
	}
};
}