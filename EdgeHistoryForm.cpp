//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#pragma hdrstop

#include "EdgeHistoryForm.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
typedef struct {
int ID;
String URL;
String Title;
} data;
sqlite3* DB;
sqlite3_stmt* stmt;
char* errmsg;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree->NodeDataSize = sizeof(data);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	int res = sqlite3_open("History", &DB);
	if (res != SQLITE_OK) {
		ShowMessage("������ �������� ���� ������");
		ExitProcess(0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DisplayHistoryButtonClick(TObject *Sender)
{
	VirtualStringTree->Clear();
	const char* sql = "SELECT * FROM urls";
	int result = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		ShowMessage("������ ���������� �������");
		sqlite3_close(DB);
		ExitProcess(0);
	}
	VirtualStringTree->BeginUpdate();
	while (true) {
		result = sqlite3_step(stmt);
		if (result != SQLITE_ROW) break;
		PVirtualNode Node = VirtualStringTree->AddChild(NULL);
		data* Data = (data*)VirtualStringTree->GetNodeData(Node);
		Data->ID = sqlite3_column_int(stmt, 0);
		Data->URL = (char*)sqlite3_column_text(stmt, 1);
		Data->Title = (WCHAR*)sqlite3_column_text16(stmt, 2);
	}
    VirtualStringTree->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	data* Data = (data*)Sender->GetNodeData(Node);
	switch (Column) {
		case 0:
			CellText = Data->ID;
			break;
		case 1:
			CellText = Data->URL;
			break;
		case 2:
			CellText = Data->Title;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTreeNodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo)
{
	PVirtualNode Node = Sender->GetFirstSelected();
	data* Data = (data*)Sender->GetNodeData(Node);
	std::string sql = "SELECT visit_count FROM urls where id=" \
	+ std::to_string(Data->ID);
	int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		ShowMessage("������ ���������� �������");
		sqlite3_close(DB);
		ExitProcess(0);
	}
	result = sqlite3_step(stmt);
	std::string vc = (char*)sqlite3_column_int(stmt, 0);
	vc = "����� ���������: " + vc;
	StringInfoLabel->Caption=vc.c_str();
}
//---------------------------------------------------------------------------

