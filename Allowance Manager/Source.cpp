#include "Intro.h"

using namespace AllowanceManager;
using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Intro^ form = gcnew Intro();
    form->StartPosition = FormStartPosition::CenterScreen;
    Application::Run(form);
    return 0;
}
