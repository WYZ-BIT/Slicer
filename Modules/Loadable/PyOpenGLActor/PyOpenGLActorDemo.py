# The following code is used to the usage of the class vtkPyOpenGLActor,
# which accepts PyOpenGL scripts, and renders the scripts in a render window.
# 
# Wenyao Zhang
# Beijing Institute of Technology
# zhwenyao@bit.edu.cn  
# 2015-03-16

import sys
# Please change the path to the python-install/DLLs in Slicer build for your sys
sys.path.append('D:/SL4/S4BD/python-install/DLLs')

# the following line is not necessary, 
# if vtkPyOpenGLActor is installed in Slicer's sys path
# sys.path.append('<Path for the lib of vtkPyOpenGLActor>')

import vtk

from OpenGL.GL import *  # for OpenGL calls
from OpenGL.GLU import *

from vtkSlicerPyOpenGLActorPython import *  # for vtkPyOpenGLActor

#--------------------------
def Render():
    glDisable(GL_LIGHTING)
    
    glMatrixMode(GL_MODELVIEW) 
    glPushMatrix()
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glPointSize(5.0)
    
    #
    glColor3f(1.0, 0.0, 0.0)
    glBegin(GL_LINES) # two red lines
    glVertex3f(-30.0, 0.0,0.0)
    glVertex3f(30.0, 0.0,0.0)
    glVertex3f(0.0, 30.0,0.0)
    glVertex3f(0.0, -30.0,0.0)
    glEnd()
    
    #
    glColor3f(0.0, 0.0, 1.0)
    glBegin(GL_LINES)# a blue curve
    for x in (i*0.1 for i in range(-300, 300)):
        y = (x * x)*0.1
        glVertex2f(x, y) #
    glEnd()
    
    glPopMatrix()
    glFlush()

# Obtain the rendering objects of Slicer
# -----------------------------------------------
ren = slicer.app.layoutManager().threeDWidget(0).threeDView().renderWindow().GetRenderers().GetFirstRenderer()
renWin=slicer.app.layoutManager().threeDWidget(0).threeDView().renderWindow()
actors=ren.GetActors()
actor=actors.GetLastActor()
mapper=actor.GetMapper();

# Drawing someting using the vtkPyOpenGLActor
# -------------------------------------------
sactor=vtkPyOpenGLActor()
sactor.SetMapper(mapper)     # This is necessary
sactor.SetScript('Render()') # Set the PyOpenGL scripts

ren.AddActor(sactor)
renWin.Render()

'''
# clear the sactor
ren.RemoveActor(sactor)
renWin.Render()
del sactor
'''

