using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using Firebase.Auth;
namespace NETLoader
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            var authprovider = new FirebaseAuthProvider(new FirebaseConfig("AIzaSyDjByUWTltyaDyZCp5OfGkfw1jrWikL7tA"));
            var auth = authprovider.SignInWithEmailAndPasswordAsync("someuser@mail.com", "password");
            auth.Wait();
            var user = auth.Result.User;
            var mail = user.Email;
            var uid = user.LocalId;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
