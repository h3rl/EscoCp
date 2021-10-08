#pragma once

#pragma comment( lib, "Advapi32.lib" )
#pragma comment( lib, "Rpcrt4.lib" )
#pragma comment( lib, "Ole32.lib" )
#pragma comment( lib, "Winhttp.lib" )
#pragma comment( lib, "Crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")

#pragma comment(lib,"firebase_admob.lib")
#pragma comment(lib,"firebase_analytics.lib")
#pragma comment(lib,"firebase_app.lib")
#pragma comment(lib,"firebase_auth.lib")
#pragma comment(lib,"firebase_database.lib")
#pragma comment(lib,"firebase_dynamic_links.lib")
#pragma comment(lib,"firebase_firestore.lib")
#pragma comment(lib,"firebase_functions.lib")
#pragma comment(lib,"firebase_installations.lib")
#pragma comment(lib,"firebase_instance_id.lib")
#pragma comment(lib,"firebase_messaging.lib")
#pragma comment(lib,"firebase_remote_config.lib")
#pragma comment(lib,"firebase_storage.lib")

#include "firebase/auth.h"
#include "firebase/app.h"
#include <firebase/auth.h>
#include <firebase/future.h>
#include <firebase/database/listener.h>
#include <firebase/database/data_snapshot.h>
#include <firebase/database/query.h>
#include <firebase/firestore.h>

#include "debug.h"

using std::string;

class MyAuthStateListener : public firebase::auth::AuthStateListener
{
public:
    void OnAuthStateChanged(firebase::auth::Auth* auth) override
    {
        firebase::auth::User* user = auth->current_user();
        if (user != nullptr)
        {
            //signed in
            _D("user " << user->uid().c_str() << " signed in");

            string displayName = user->display_name();
            string email = user->email();
            string photo = user->photo_url();

            _D(displayName << " " << email << " " << photo);
           
            
        }
        else {
            _D("signed out");
        }

    }
};

bool SignInWithEmail(firebase::auth::Auth* auth,const char* email, const char* password)
{
    firebase::Future<firebase::auth::User*> future = auth->SignInWithEmailAndPasswordLastResult();
    do {
        if (future.status() == firebase::kFutureStatusInvalid ||
            (future.status() == firebase::kFutureStatusComplete &&
                future.error() != firebase::auth::kAuthErrorNone))
        {
            auth->SignInWithEmailAndPassword(email,password);
            return true;
        }
    } while (future.status() == firebase::kFutureStatusPending);
    return false;
}
