//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
using namespace std;
TForm1 *Form1;
sqlite3* BD;
int del_id;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1 -> NodeDataSize = sizeof(TableStruct);
	Button2 -> Enabled = False;
	Button3 -> Enabled = False;
	Button4 -> Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;
		TableStruct *nodeData = (TableStruct*)VirtualStringTree1 ->
		GetNodeData(Node);

		switch (Column)
		{

			case 0:
			{
				CellText = UnicodeString(nodeData -> id);  break;
			}
			case 1:
			{
				CellText = nodeData -> host; break;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int res = sqlite3_open16(L".\\places.sqlite", &BD);
	if (res!=SQLITE_OK)
	{
		Label2 -> Caption = L"Can't open DB!";
		return void();
	}
	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	sqlite3_stmt *stmt;
	res = sqlite3_prepare16_v2(BD,
	L"SELECT * FROM moz_origins ORDER BY id;", -1, &stmt, NULL);
	if (res!=SQLITE_OK)
	{
		Label2 -> Caption = L"Can't complete request!";
		return void();
	}
	 while(true)
		{
			res = sqlite3_step(stmt);
			if(res == SQLITE_DONE) break;
			else if (res == SQLITE_ROW)
			{
				PVirtualNode mainNode = VirtualStringTree1
				-> AddChild(VirtualStringTree1 -> RootNode);
				TableStruct *nodeData =
				(TableStruct*)VirtualStringTree1 -> GetNodeData(mainNode);
				nodeData -> id = sqlite3_column_int(stmt,0);
				nodeData -> prefix =
				(UnicodeString)(char*)sqlite3_column_text(stmt,1);
				nodeData -> host =
				(UnicodeString)(char*)sqlite3_column_text(stmt,2);
				nodeData -> frecency = sqlite3_column_int(stmt,3);
			 }
			else
			{
				Label2 -> Caption = L"Can't read table!";
				break;
			}
		}
	sqlite3_finalize(stmt);
	VirtualStringTree1 -> EndUpdate();
	Label2 -> Caption = L"DB is opened!";
	Button3 -> Enabled = True;
	Button4 -> Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	 sqlite3_close(BD);
	 Label2 -> Caption = L"DB is closed!";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
          PVirtualNode Node)
{
    if (!Node) return;
	Button2 -> Enabled = True;
	TableStruct *nodeData = (TableStruct*)VirtualStringTree1 ->
	GetNodeData(Node);
	del_id = nodeData -> id;
	Memo1 -> Clear();
	Memo1 -> Lines -> Add(L"Prefix: " + nodeData -> prefix);
	Memo1 -> Lines -> Add(L"Frecency: " + UnicodeString(nodeData -> frecency));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	VirtualStringTree1 -> Clear();
	sqlite3_stmt *stmt;
	int res = sqlite3_prepare16_v2(BD,
	L"DELETE FROM moz_origins; VACUUM;", -1, &stmt, NULL);
	if (res!=SQLITE_OK)
	{
		Label2 -> Caption = L"Can't complete request!";
		return void();
	}

	res = sqlite3_step(stmt);
	if(res!=SQLITE_DONE)
	{
		Label2 -> Caption = L"Can't clean DB!";
        return;
	}
	sqlite3_finalize(stmt);
	Label2 -> Caption = L"Table is eraised!";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	sqlite3_stmt *stmt;
	wstring del = L"DELETE FROM moz_origins WHERE id = " + to_wstring(del_id) + L";";
	const wchar_t* req = del.c_str();
	int res = sqlite3_prepare16_v2(BD, req, -1, &stmt, NULL);
	if(res != SQLITE_OK)
	{
		Label2 -> Caption = L"Can't complete reques!";
		return void();
	}
	res = sqlite3_step(stmt);

	if(res!=SQLITE_DONE)
	{
		Label2 -> Caption = L"Error while delete from table!";
		return void();
	}
	sqlite3_finalize(stmt);

	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	res = sqlite3_prepare16_v2(BD,
	L"SELECT * FROM moz_origins ORDER BY id;", -1, &stmt, NULL);
	if (res!=SQLITE_OK)
	{
		Label2 -> Caption = L"Can't complete request!";
		return void();
	}
	while(true)
		{
			res = sqlite3_step(stmt);
			if(res == SQLITE_DONE) break;
			else if (res == SQLITE_ROW)
			{
				PVirtualNode mainNode = VirtualStringTree1
				-> AddChild(VirtualStringTree1 -> RootNode);
				TableStruct *nodeData =
				(TableStruct*)VirtualStringTree1 -> GetNodeData(mainNode);
				nodeData -> id = sqlite3_column_int(stmt,0);
				nodeData -> prefix =
				(UnicodeString)(char*)sqlite3_column_text(stmt,1);
				nodeData -> host =
				(UnicodeString)(char*)sqlite3_column_text(stmt,2);
				nodeData -> frecency = sqlite3_column_int(stmt,3);
			 }
			else
			{
				Label2 -> Caption = L"Can't read table!";
				break;
			}
		}
	sqlite3_finalize(stmt);
	VirtualStringTree1 -> EndUpdate();
	Label2 -> Caption = L"Record is deleted!";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	sqlite3_close(BD);
}
//---------------------------------------------------------------------------

