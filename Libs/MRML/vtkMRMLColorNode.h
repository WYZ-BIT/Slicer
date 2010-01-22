/*=auto=========================================================================

  Portions (c) Copyright 2006 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLColorNode.h,v $
  Date:      $Date: 2006/03/19 17:12:28 $
  Version:   $Revision: 1.0 $

=========================================================================auto=*/
///  vtkMRMLColorNode - MRML node to represent color information.
/// 
/// Color nodes describe colour look up tables. The tables may be pre-generated by
/// Slicer (the label map colours, some default ramps, a random one) or created by
/// a user. More than one model or label volume or editor can access the prebuilt
/// nodes. This is used as a superclass for table based, procedural based, and
/// implicit function based color nodes

#ifndef __vtkMRMLColorNode_h
#define __vtkMRMLColorNode_h

#include <string>
#include <vector>

#include "vtkMRML.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLStorableNode.h"

#include "vtkLookupTable.h"

class VTK_MRML_EXPORT vtkMRMLColorNode : public vtkMRMLStorableNode
{
public:
  static vtkMRMLColorNode *New();
  vtkTypeMacro(vtkMRMLColorNode,vtkMRMLStorableNode);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  //--------------------------------------------------------------------------
  /// MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance();

  /// 
  /// Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  /// 
  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);


  /// 
  /// Read in a text file holding colours
  /// Return 1 on sucess, 0 on failure
  virtual int ReadFile ();
  
  /// 
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);
  
  /// 
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "Color";};

  /// 
  /// Reset node attributes to the initilal state as defined in the constructor.
  /// NOTE:   it preserves values several dynamic attributes that may be set by an application: type, name
  virtual void Reset();
  
  /// 
  /// 
  virtual void UpdateScene(vtkMRMLScene *scene);

  /// 
  /// Set Type to type, then build colours and set names
  virtual void SetType(int type);
  /// 
  /// Get for Type
  vtkGetMacro(Type,int);

  void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, void *callData );

  /// 
  /// Return the lowest and the highest type integers (defined in enum in
  /// subclass), for use in looping
  virtual int GetFirstType();
  virtual int GetLastType ();
  
  /// 
  /// return a text string describing the colour look up table type
  virtual const char * GetTypeAsString();

  //BTX
  /// 
  /// TypeModifiedEvent is generated when the type of the colour look up table changes
  enum
    {
      TypeModifiedEvent = 20002,
    };
//ETX

  /// 
  /// Get the 0th based nth name of this colour
  const char *GetColorName(int ind);
  /// 
  /// Get the 0th based nth name of this colour, replacing the spaces with
  /// subst
  //BTX
  std::string GetColorNameWithoutSpaces(int ind, const char *subst);
  //ETX
  
  /// 
  /// Add a color name to the vector
  void AddColorName(const char *name);
  /// 
  /// Set the 0th based nth name of this colour
  void SetColorName(int ind, const char *name);
  /// 
  /// Set the 0th based nth name of this colour, replacing the subst character
  /// with spaces
  void SetColorNameWithSpaces(int ind, const char *name, const char *subst);
  
  /// 
  /// Name of the file name from which to read color information
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  /// 
  /// Most color nodes will implement a look up table, so provide a top level
  /// get method
  virtual vtkLookupTable * GetLookupTable();

  /// 
  /// get/set the string used for an unnamed colour
  vtkGetStringMacro(NoName);
  vtkSetStringMacro(NoName);

  /// 
  /// Get/Set for the flag on names array having been initalised
  vtkGetMacro(NamesInitialised, int);
  vtkSetMacro(NamesInitialised, int);
  vtkBooleanMacro(NamesInitialised, int);

  virtual bool CanApplyNonLinearTransforms() { return false; }
  virtual void ApplyTransform(vtkAbstractTransform* vtkNotUsed(transform)) { return; };
  virtual void ApplyTransform(vtkMatrix4x4* transformMatrix)
    { Superclass::ApplyTransform(transformMatrix); }
 
  /// 
  /// Create default storage node or NULL if does not have one
  virtual vtkMRMLStorageNode* CreateDefaultStorageNode()
    {
    return Superclass::CreateDefaultStorageNode();
    };

protected:
  vtkMRMLColorNode();
  virtual ~vtkMRMLColorNode();
  vtkMRMLColorNode(const vtkMRMLColorNode&);
  void operator=(const vtkMRMLColorNode&);

  /// 
  /// Set values in the names vector from the colours in the node
  virtual void SetNamesFromColors();
  
  /// 
  /// Which type of look up table does this node hold? 
  /// Valid values are in the enumerated list
  int Type;

  //BTX
  /// 
  /// A vector of names for the color table elements
  std::vector<std::string> Names;
  //ETX

  /// 
  /// A file name to read text attributes from
  char *FileName;

  /// 
  /// the string used for an unnamed colour
  char *NoName;

  /// 
  /// Have the colour names been set? Used to do lazy copy of the Names array.
  int NamesInitialised;
};

#endif
