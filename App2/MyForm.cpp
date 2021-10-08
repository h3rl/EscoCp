#include "MyForm.h"
using namespace System;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Threading;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;
using namespace MetroFramework::Forms;
using namespace MetroFramework;


void Main(array<String^>^ args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	EscoCp::App^ app = gcnew EscoCp::App();

	System::Windows::Forms::Application::Run(app);
}