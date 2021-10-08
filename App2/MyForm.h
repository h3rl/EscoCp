#pragma once


namespace EscoCp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace MetroFramework::Forms;
	using namespace MetroFramework;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class App : public MetroFramework::Forms::MetroForm
	{
#pragma region Initialization
	public:
		App(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~App()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma endregion Initialization
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// App
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(935, 646);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(5, 6, 5, 6);
			this->MaximizeBox = false;
			this->Name = L"App";
			this->Padding = System::Windows::Forms::Padding(0, 111, 0, 0);
			this->Resizable = false;
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::WindowsDefaultLocation;
			this->Text = L"E S C O";
			this->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->TopMost = true;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
