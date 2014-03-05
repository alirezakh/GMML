#ifndef TOPOLOGYDIHEDRAL_HPP
#define TOPOLOGYDIHEDRAL_HPP

#include <string>
#include <iostream>
#include <vector>

namespace TopologyFileSpace
{
    /*! \enum
      * Topology positional dihedral type enumerator
      */
        enum TopologyPositionalDihedralType
        {
            INTER_RESIDUE_DIHEDRAL_ = 1,
            INTRA_RESIDUE_DIHEDRAL_ = 2
        };
        /*! \enum
          * Topology rotational dihedral type enumerator
          */
            enum TopologyRotationalDihedralType
            {
                INTER_RESIDUE_ROTATIONAL_AXIS_ = 1,
                INTRA_RESIDUE_ROTATIONAL_AXIS_ = 2
            };

    class TopologyDihedralType;

    class TopologyDihedral
    {
        public:
            //////////////////////////////////////////////////////////
            //                       CONSTRUCTOR                    //
            //////////////////////////////////////////////////////////
            /*! \fn
              * Default constructor
              */
            TopologyDihedral();

            //////////////////////////////////////////////////////////
            //                       ACCESSOR                       //
            //////////////////////////////////////////////////////////
            /*! \fn
              * An accessor function in order to access to the dihedrals
              * @return dihedrals_ attribute of the current object of this class
              */
            std::vector<std::string> GetDihedrals();
            /*! \fn
              * An accessor function in order to access to the dihedral type
              * @return dihedral_type_ attribute of the current object of this class
              */
            TopologyDihedralType* GetDihedralType();
            /*! \fn
              * An accessor function in order to access to boolean value that indicates if dihedral is improper
              * @return is_improper_ attribute of the current object of this class
              */
            bool GetIsImproper();
            /*! \fn
              * An accessor function in order to access to boolean value that indicates if dihedral is in ignored group interaction
              * @return ignored_group_interaction_ attribute of the current object of this class
              */
            bool GetIgnoredGroupInteraction();
            /*! \fn
              * An accessor function in order to access to positional dihedral type
              * @return posotional_type_ attribute of the current object of this class
              */
            TopologyPositionalDihedralType GetPositionalType();
            /*! \fn
              * An accessor function in order to access to rotational dihedral type
              * @return rotational_type_ attribute of the current object of this class
              */
            TopologyRotationalDihedralType GetRotationalType();

            //////////////////////////////////////////////////////////
            //                       MUTATOR                        //
            //////////////////////////////////////////////////////////
            /*! \fn
              * A mutator function in order to set the dihedrals of the current object
              * Set the dihedrals_ attribute of the current topology dihedral
              * @param dihedrals The dihedrals attribute of the current object
              */
            void SetDihedrals(std::vector<std::string> dihedrals);
            /*! \fn
              * A mutator function in order to set the dihedral type of the current object
              * Set the dihedral_type_ attribute of the current topology dihedral type
              * @param dihedral_type The dihedral type attribute of the current object
              */
            void SetDihedralType(TopologyDihedralType* dihedral_type);
            /*! \fn
              * A mutator function in order to set the boolean improper attribute of the current object
              * Set the is_improper_ attribute of the current topology dihedral type
              * @param is_improper The is improper attribute of the current object
              */
            void SetIsImproper(bool is_improper);
            /*! \fn
              * A mutator function in order to set the boolean ignored group interaction of the current object
              * Set the ignored_group_interaction_ attribute of the current topology dihedral type
              * @param ignored_group_interaction The ignored group interactionr attribute of the current object
              */
            void SetIgnoredGroupInteraction(bool ignored_group_interaction);
            /*! \fn
              * A mutator function in order to set the positional type of the current object
              * Set the positional_type_ attribute of the current topology dihedral type
              * @param positional_type The positional_type attribute of the current object
              */
            void SetPositionalType(TopologyPositionalDihedralType positional_type);
            /*! \fn
              * A mutator function in order to set the rotational type of the current object
              * Set the rotational_type_ attribute of the current topology dihedral type
              * @param rotational_type The positional_type attribute of the current object
              */
            void SetRotationalType(TopologyRotationalDihedralType rotational_type);

            //////////////////////////////////////////////////////////
            //                        FUNCTIONS                     //
            //////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////
            //                       DISPLAY FUNCTION               //
            //////////////////////////////////////////////////////////
            /*! \fn
              * A function to print out the topology dihedral contents in a structural format
              * Print out the information in a defined structure
              * @param out An output stream, the print result will be written in the given output stream
              */
            void Print(std::ostream& out = std::cout);

        private:
            //////////////////////////////////////////////////////////
            //                       ATTRIBUTES                     //
            //////////////////////////////////////////////////////////
            std::vector<std::string> dihedrals_;
            TopologyDihedralType* dihedral_type_;
            bool is_improper_;
            bool ignored_group_interaction_;
            TopologyPositionalDihedralType positional_type_;
            TopologyRotationalDihedralType rotational_type_;

    };
}

#endif // TOPOLOGYDIHEDRAL_HPP
