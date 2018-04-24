# Lab EC 1 - Virtual Trackball

*You may work in pairs. To receive credit, demonstrate your completed program
during lab or push your code up to Bitbucket prior to class on the due date.*

**THIS IS EXTRA CREDIT.  While you may find the content helpful, it is not
required.**

In this lab, you’ll learn about an intuitive camera control called a virtual
trackball. A virtual trackball takes 2D mouse or touch movements and converts
them into a 3D rotation that mimics a trackball. A torus has been provided.
It is your job to implement a virtual trackball to rotate
our view of the scene (or more appropriately rotate our scene in front of our
camera).

## Recommended Reading

[Rotating arbitrary axis](http://paulbourke.net/geometry/rotate/)
[Object Mouse Trackball](https://www.opengl.org/wiki/Object_Mouse_Trackball)

## Part 1 - Rotate about an arbitrary axis

Previously, we have seen how to rotate about a coordinate axis.  But, what if we
want to rotate about an arbitrary axis?  Later in the semester, we will see how
to use quaternions, but for now, we will build on the matrix transformations
that we have already built.

Read and implement the algorithm described by Paul Bourke for [rotating about an
arbitrary axis](http://paulbourke.net/geometry/rotate/)

## Part 2 - Virtual trackball surface equations

Next, we will implement the equations necessary to convert a 2D mouse click to a
3D point on the virtual trackball surface.  Implement a function
pointOnVirtualTrackball, which will be used in the next parts. See [Object Mouse
Trackball](https://www.opengl.org/wiki/Object_Mouse_Trackball) for the equations
to use.

## Part 3 - Construct a rotation matrix

When the user clicks and drags on the screen, we need to use that information to
construct a rotation matrix that will change our view. Start by converting each
click or move event using the pointOnVirtualTrackball method from Part 2. Keep
track of the previous event’s location in addition to the current one. Take
those two vectors and solve for the angle between them using the dot product.
Then solve for a unit vector perpendicular to the two vectors to find the axis
of rotation using the cross product.

Use the angle and axis values to construct a rotation matrix using the method
from Part 1.  Keep track of all your rotations by continuously multiplying your
rotations together. Create a trackball matrix variable that is initialized to
the identity matrix. After each rotation, multiply it into your trackball
matrix.

## Part 4 - Part 3 - Transform our view

Rather than think of our view changing, think of the scene rotating in front of
us. Adjust your vertex shader to accept another matrix for your trackball
transformation and multiply it in your chain of transformations in the correct
order.

## Things to notice

When you click and drag the scene should rotate in the same direction. If it
seems to be rotating opposite, you may be crossing your vectors in reverse
order.
