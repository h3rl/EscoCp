#include "form.h"
#include "debug.h"

#include "fbase.h"


using namespace System;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Threading;


void Main(array<String^>^ args)
{
	createDbgConsole();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	auto appOptions = firebase::AppOptions();
	appOptions.set_api_key("AIzaSyAl07gIDiogDxs4Ar2kHSixXABLsmViU8E");
	appOptions.set_app_id("1:392694231072:web:dd5647fd3d378135160c45");
	appOptions.set_database_url("https://esco-e57a4-default-rtdb.europe-west1.firebasedatabase.app");
	//appOptions.set_ga_tracking_id("");
	appOptions.set_messaging_sender_id("392694231072");
	appOptions.set_project_id("esco-e57a4");
	appOptions.set_storage_bucket("esco-e57a4.appspot.com");

	auto app = firebase::App::Create(appOptions);
	auto auth = firebase::auth::Auth::GetAuth(app);

	MyAuthStateListener authStateListener;
	auth->AddAuthStateListener(&authStateListener);

	auto res = auth->SignInWithEmailAndPassword("halvard.erla@gmail.com", "Nottos23");

	while (res.status() == firebase::kFutureStatusPending)
	{
		Sleep(100);
	}
	_D("loginstatus: " << res.status());

	auto user = auth->current_user();

	if (user != nullptr) {
		std::string name = user->display_name();
		std::string email = user->email();
		std::string photo_url = user->photo_url();
		// The user's ID, unique to the Firebase project.
		// Do NOT use this value to authenticate with your backend server,
		// if you have one. Use firebase::auth::User::Token() instead.
		std::string uid = user->uid();

		_D(name << " " << email << " " << photo_url << " " << uid);
	}

	NETLoader::Form^ form = gcnew NETLoader::Form();
	System::Windows::Forms::Application::Run(form);
}