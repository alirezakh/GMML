// Author: Alireza Khatamian

#include "../../../includes/FileSet/PdbFileSpace/pdbsheetcard.hpp"

using namespace std;
using namespace PdbFileSpace;

//////////////////////////////////////////////////////////
//                       CONSTRUCTOR                    //
//////////////////////////////////////////////////////////
PdbSheetCard::PdbSheetCard() : record_name_("SHEET") {}

PdbSheetCard::PdbSheetCard(const string &record_name) : record_name_(record_name) {}

//////////////////////////////////////////////////////////
//                         ACCESSOR                     //
//////////////////////////////////////////////////////////
string PdbSheetCard::GetRecordName()
{
    return record_name_;
}

PdbSheetCard::SheetMap PdbSheetCard::GetSheets()
{
    return sheets_;
}

//////////////////////////////////////////////////////////
//                          MUTATOR                     //
//////////////////////////////////////////////////////////
void PdbSheetCard::SetRecordName(const string record_name)
{
    record_name_ = record_name;
}

//////////////////////////////////////////////////////////
//                        FUNCTIONS                     //
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//                      DISPLAY FUNCTION                //
//////////////////////////////////////////////////////////
