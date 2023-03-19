//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("U_Main_form.cpp", MainForm);
USEFORM("U_About_form.cpp", About_form);
USEFORM("U_Start_form.cpp", Start_form);
USEFORM("U_Text_ed.cpp", Text_editor);
USEFORM("U_Excel_ed.cpp", Excel_editor);
USEFORM("U_Load_form.cpp", Load_form);
USEFORM("U_Reference_form.cpp", Ref_form);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAbout_form), &About_form);
		Application->CreateForm(__classid(TText_editor), &Text_editor);
		Application->CreateForm(__classid(TExcel_editor), &Excel_editor);
		Application->CreateForm(__classid(TStart_form), &Start_form);
		Application->CreateForm(__classid(TLoad_form), &Load_form);
		Application->CreateForm(__classid(TRef_form), &Ref_form);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
