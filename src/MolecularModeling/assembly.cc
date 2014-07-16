#include "../../includes/MolecularModeling/assembly.hpp"
#include "../../includes/MolecularModeling/residue.hpp"
#include "../../includes/MolecularModeling/atom.hpp"

#include "../../includes/FileSet/TopologyFileSpace/topologyfile.hpp"
#include "../../includes/FileSet/TopologyFileSpace/topologyassembly.hpp"
#include "../../includes/FileSet/TopologyFileSpace/topologyresidue.hpp"
#include "../../includes/FileSet/TopologyFileSpace/topologyatom.hpp"
#include "../../includes/FileSet/CoordinateFileSpace/coordinatefile.hpp"
#include "../../includes/ParameterSet/PrepFileSpace/prepfile.hpp"
#include "../../includes/ParameterSet/PrepFileSpace/prepfileresidue.hpp"
#include "../../includes/ParameterSet/PrepFileSpace/prepfileatom.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbfile.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbmodelcard.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbmodel.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbmodelresidueset.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbatomcard.hpp"
#include "../../includes/FileSet/PdbFileSpace/pdbheterogenatomcard.hpp"

using namespace std;
using namespace MolecularModeling;
using namespace TopologyFileSpace;
using namespace CoordinateFileSpace;
using namespace PrepFileSpace;
using namespace PdbFileSpace;
using namespace Geometry;

//////////////////////////////////////////////////////////
//                       CONSTRUCTOR                    //
//////////////////////////////////////////////////////////
Assembly::Assembly() {}

Assembly::Assembly(vector<string> file_paths, gmml::InputFileType type)
{
    source_file_type_ = type;
    switch(type)
    {
        case gmml::PDB:
            source_file_ = file_paths.at(0);
            BuildAssemblyFromPdbFile(source_file_);
            break;
        case gmml::TOP:
            source_file_ = file_paths.at(0);
            BuildAssemblyFromTopologyFile(source_file_);
            break;
        case gmml::LIB:
            source_file_ = file_paths.at(0);
//            BuildAssemblyFromLibraryFile(source_file_);
            break;
        case gmml::PREP:
            source_file_ = file_paths.at(0);
            BuildAssemblyFromPrepFile(source_file_);
            break;
        case gmml::TOP_CRD:
            source_file_ = file_paths.at(0)+";"+file_paths.at(1);
              BuildAssemblyFromTopologyCoordinateFile(file_paths.at(0), file_paths.at(1));
            break;
    }
}

//////////////////////////////////////////////////////////
//                         ACCESSOR                     //
//////////////////////////////////////////////////////////
string Assembly::GetName()
{
    return name_;
}
Assembly::AssemblyVector Assembly::GetAssemblies()
{
    return assemblies_;
}
Assembly::ResidueVector Assembly::GetResidues()
{
    return residues_;
}
string Assembly::GetChemicalType()
{
    return chemical_type_;
}
int Assembly::GetSequenceNumber()
{
    return sequence_number_;
}
double Assembly::GetTotalMass()
{
    return total_mass_;
}
Geometry::Coordinate Assembly::GetCenterOfMass()
{
    return center_of_mass_;
}
Geometry::Coordinate Assembly::GetCenterOfGeometry()
{
    return center_of_geometry_;
}
string Assembly::GetDescription()
{
    return description_;
}
string Assembly::GetSourceFile()
{
    return source_file_;
}
gmml::InputFileType Assembly::GetSourceFileType()
{
    return source_file_type_;
}

//////////////////////////////////////////////////////////
//                          MUTATOR                     //
//////////////////////////////////////////////////////////
void Assembly::SetName(string name)
{
    name_ = name;
}
void Assembly::SetAssemblies(AssemblyVector assemblies)
{
    assemblies_ = assemblies;
}
void Assembly::AddAssembly(Assembly *assembly)
{
    assemblies_.push_back(assembly);
}
void Assembly::SetResidues(ResidueVector residues)
{
    residues_ = residues;
}
void Assembly::AddResidue(Residue *residue)
{
    residues_.push_back(residue);
}
void Assembly::SetChemicalType(string chemical_type)
{
    chemical_type_ = chemical_type;
}
void Assembly::SetSequenceNumber(int sequence_number)
{
    sequence_number_ = sequence_number;
}
void Assembly::SetTtoalMass(double total_mass)
{
    total_mass_ = total_mass;
}
void Assembly::SetCenterOfMass(Geometry::Coordinate center_of_mass)
{
    center_of_mass_ = center_of_mass;
}
void Assembly::SetCenterOfGeometry(Geometry::Coordinate center_of_geometry)
{
    center_of_geometry_ = center_of_geometry;
}
void Assembly::SetDescription(string description)
{
    description_ = description;
}
void Assembly::SetSourceFile(string source_file)
{
    source_file_ = source_file;
}
void Assembly::SetSourceFileType(gmml::InputFileType source_file_type)
{
    source_file_type_ = source_file_type;
}
//////////////////////////////////////////////////////////
//                       FUNCTIONS                      //
//////////////////////////////////////////////////////////
void Assembly::BuildAssemblyFromPdbFile(string pdb_file_path)
{
    PdbFile* pdb_file = new PdbFile(pdb_file_path);
    PdbFile::PdbResidueAtomsMap residue_atoms_map = pdb_file->GetAllAtomsOfResidues();
    for(PdbFile::PdbResidueAtomsMap::iterator it = residue_atoms_map.begin(); it != residue_atoms_map.end(); it++)
    {
        PdbFile::PdbAtomVector* atoms = (*it).second;
        Residue* residue = new Residue();        
        residue->SetAssembly(this);
        int atom_counter = 0;

        for(PdbFile::PdbAtomVector::iterator it1 = atoms->begin(); it1 != atoms->end(); it1++)
        {
            PdbAtom* atom = (*it1);
            string residue_name = atom->GetAtomResidueName();
            char chain_id = atom->GetAtomChainId();
            int sequence_number = atom->GetAtomResidueSequenceNumber();
            char insertion_code = atom->GetAtomInsertionCode();
            char alternate_location = atom->GetAtomAlternateLocation();
            stringstream ss;
            ss << residue_name << "_" << chain_id << "_" << sequence_number << "_" << insertion_code << "_" << alternate_location;
            string key = ss.str();

            Atom* new_atom = new Atom();
            residue->SetName(residue_name);
            new_atom->SetName(atom->GetAtomName());
            new_atom->SetResidue(residue);
            for(PdbModelCard::PdbModelMap::iterator it2 = pdb_file->GetModels()->GetModels().begin(); it2 != pdb_file->GetModels()->GetModels().end(); it2++)
            {
                PdbModel* model = (*it2).second;
                PdbModelResidueSet* residue_set = model->GetModelResidueSet();
                for(PdbModelResidueSet::AtomCardVector::iterator it3 = residue_set->GetAtoms().begin(); it3 != residue_set->GetAtoms().end(); it3++)
                {
                    PdbAtomCard* atom_card = (*it3);
                    for(PdbAtomCard::PdbAtomMap::iterator it4 = atom_card->GetAtoms().begin(); it4 != atom_card->GetAtoms().end(); it4++)
                    {
                        PdbAtom* matching_atom = (*it4).second;
                        string matching_residue_name = matching_atom->GetAtomResidueName();
                        char matching_chain_id = matching_atom->GetAtomChainId();
                        int matching_sequence_number = matching_atom->GetAtomResidueSequenceNumber();
                        char matching_insertion_code = matching_atom->GetAtomInsertionCode();
                        char matching_alternate_location = matching_atom->GetAtomAlternateLocation();
                        stringstream sss;
                        sss << matching_residue_name << "_" << matching_chain_id << "_" << matching_sequence_number << "_"
                           << matching_insertion_code << "_" << matching_alternate_location;
                        string matching_key = sss.str();

                        if(key.compare(matching_key) == 0)
                        {
                            Geometry::Coordinate* coordinate = new Geometry::Coordinate(matching_atom->GetAtomOrthogonalCoordinate());
                            new_atom->AddCoordinate(coordinate);
                        }
                    }
                }
                for(PdbModelResidueSet::HeterogenAtomCardVector::iterator it3 = residue_set->GetHeterogenAtoms().begin(); it3 != residue_set->GetHeterogenAtoms().end(); it3++)
                {
                    PdbHeterogenAtomCard* heterogen_atom_card = (*it3);
                    for(PdbAtomCard::PdbAtomMap::iterator it4 = heterogen_atom_card->GetHeterogenAtoms().begin(); it4 != heterogen_atom_card->GetHeterogenAtoms().end(); it4++)
                    {
                        PdbAtom* matching_atom = (*it4).second;
                        string matching_residue_name = matching_atom->GetAtomResidueName();
                        char matching_chain_id = matching_atom->GetAtomChainId();
                        int matching_sequence_number = matching_atom->GetAtomResidueSequenceNumber();
                        char matching_insertion_code = matching_atom->GetAtomInsertionCode();
                        char matching_alternate_location = matching_atom->GetAtomAlternateLocation();
                        stringstream sss;
                        sss << matching_residue_name << "_" << matching_chain_id << "_" << matching_sequence_number << "_"
                           << matching_insertion_code << "_" << matching_alternate_location;
                        string matching_key = sss.str();

                        if(key.compare(matching_key) == 0)
                        {
                            Geometry::Coordinate* coordinate = new Geometry::Coordinate(matching_atom->GetAtomOrthogonalCoordinate());
                            new_atom->AddCoordinate(coordinate);
                        }
                    }
                }
            }
            residue->AddAtom(new_atom);
        }
        this->AddResidue(residue);
    }

}

void Assembly::BuildAssemblyFromTopologyFile(string topology_file_path)
{
    TopologyFile* topology_file = new TopologyFile(topology_file_path);
    name_ = topology_file->GetTitle();
    sequence_number_ = 1;
    TopologyAssembly::TopologyResidueMap topology_residues = topology_file->GetAssembly()->GetResidues();
    for(TopologyAssembly::TopologyResidueMap::iterator it = topology_residues.begin(); it != topology_residues.end(); it++)
    {
        Residue* assembly_residue = new Residue();
        assembly_residue->SetAssembly(this);
        assembly_residue->SetName((*it).first);
        TopologyResidue* topology_residue = (*it).second;

        TopologyResidue::TopologyAtomMap topology_atoms = topology_residue->GetAtoms();
        for(TopologyResidue::TopologyAtomMap::iterator it1 = topology_atoms.begin(); it1 != topology_atoms.end(); it1++)
        {
            Atom* assembly_atom = new Atom();
            assembly_atom->SetName((*it1).first);
            TopologyAtom* topology_atom = (*it1).second;

            assembly_atom->SetResidue(assembly_residue);
            assembly_atom->SetName(topology_atom->GetAtomName());

            assembly_residue->AddAtom(assembly_atom);
        }
        residues_.push_back(assembly_residue);

    }
}

void Assembly::BuildAssemblyFromTopologyCoordinateFile(string topology_file_path, string coordinate_file_path)
{
    TopologyFile* topology_file = new TopologyFile(topology_file_path);
    name_ = topology_file->GetTitle();
    sequence_number_ = 1;
    TopologyAssembly::TopologyResidueMap topology_residues = topology_file->GetAssembly()->GetResidues();
    for(TopologyAssembly::TopologyResidueMap::iterator it = topology_residues.begin(); it != topology_residues.end(); it++)
    {
        Residue* assembly_residue = new Residue();
        assembly_residue->SetAssembly(this);
        assembly_residue->SetName((*it).first);
        TopologyResidue* topology_residue = (*it).second;

        TopologyResidue::TopologyAtomMap topology_atoms = topology_residue->GetAtoms();
        for(TopologyResidue::TopologyAtomMap::iterator it1 = topology_atoms.begin(); it1 != topology_atoms.end(); it1++)
        {
            Atom* assembly_atom = new Atom();
            assembly_atom->SetName((*it1).first);
            TopologyAtom* topology_atom = (*it1).second;

            int topology_atom_index = topology_atom->GetIndex();

            assembly_atom->SetResidue(assembly_residue);
            assembly_atom->SetName(topology_atom->GetAtomName());

            CoordinateFile* coordinate_file = new CoordinateFile(coordinate_file_path);
            vector<Geometry::Coordinate*> coord_file_coordinates = coordinate_file->GetCoordinates();
            assembly_atom->AddCoordinate(coord_file_coordinates.at(topology_atom_index));
            assembly_residue->AddAtom(assembly_atom);
        }
        residues_.push_back(assembly_residue);

    }
}

void Assembly::BuildAssemblyFromPrepFile(string prep_file_path)
{
    PrepFile* prep_file = new PrepFile(prep_file_path);
    sequence_number_ = 1;
    PrepFile::ResidueMap prep_residues = prep_file->GetResidues();
    for(PrepFile::ResidueMap::iterator it = prep_residues.begin(); it != prep_residues.end(); it++)
    {
        Residue* assembly_residue = new Residue();
        assembly_residue->SetAssembly(this);
        assembly_residue->SetName((*it).first);
        PrepFileResidue* prep_residue = (*it).second;

        PrepFileResidue::PrepFileAtomVector prep_atoms = prep_residue->GetAtoms();
        for(PrepFileResidue::PrepFileAtomVector::iterator it1 = prep_atoms.begin(); it1 != prep_atoms.end(); it1++)
        {
            Atom* assembly_atom = new Atom();
            PrepFileAtom* prep_atom = (*it1);

            assembly_atom->SetResidue(assembly_residue);
            assembly_atom->SetName(prep_atom->GetName());

            assembly_residue->AddAtom(assembly_atom);
        }
        residues_.push_back(assembly_residue);

    }
}

//////////////////////////////////////////////////////////
//                      DISPLAY FUNCTION                //
//////////////////////////////////////////////////////////
void Assembly::Print(ostream &out)
{
}
