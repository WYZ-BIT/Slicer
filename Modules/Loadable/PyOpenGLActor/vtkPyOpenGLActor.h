
#ifndef __vtkPyOpenGLActor_h
#define __vtkPyOpenGLActor_h

#include "vtkSlicerPyOpenGLActorExport.h"

// VTK includes
#include "vtkActor.h"

class vtkOpenGLRenderer;

class VTK_SLICER_PYOPENGLACTOR_EXPORT vtkPyOpenGLActor : public vtkActor
{
protected:
  
public:
  static vtkPyOpenGLActor *New();
  vtkTypeMacro(vtkPyOpenGLActor,vtkActor); 
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Actual actor render method.
  void Render(vtkRenderer *ren, vtkMapper *mapper);

  // Description:
  // The string to execute to implement rendering of the actor
  // - user should embed references to appropriate Renderer, Actor and Mapper
  //   in the script so it can reference the data contained in them in order
  //   to implement the rendering
  vtkGetStringMacro(Script);
  vtkSetStringMacro(Script);

protected:
  vtkPyOpenGLActor();
  ~vtkPyOpenGLActor();

private:
  vtkPyOpenGLActor(const vtkPyOpenGLActor&);  // Not implemented.
  void operator=(const vtkPyOpenGLActor&);  // Not implemented.

  char *Script;
};

#endif

