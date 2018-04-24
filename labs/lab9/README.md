# Lab 9 - Animating Orientation

*You may work in pairs on this assignment. To receive credit, demonstrate your
completed program during lab or push your code up to Bitbucket prior to class on
the due date.*

So far we have used matrices to represent orientations. Remember that a 3x3
matrix is required to represent a 3D orientation, so a minimum of 9 values.
Quaternions are another representation of orientation that uses only 4 values.
Quaternions also provide a nice mathematical means of interpolating between two
quaternions along the shortest path, called spherical linear interpolation, or
slerp. Euler angles are another way of representing orientation and are often
the form exposed to animation artists. Conceptually, Euler angles are easier to
grasp than quaternions, but suffer from gimbal lock, where you can lose the
ability to rotate about an axis in certain configurations. In this lab, we’ll
explore the difference between animating these different orientation
representations.


## Recommended Reading

* [Quaternions and spatial rotations](http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
* [Rotations - OpenGL Tutorial](http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/)
* [glm quaternion API](http://glm.g-truc.net/0.9.4/api/a00153.html)

## General Setup

The vector `rotations` contains an ordered list of Euler angle rotations and is
used to represent our key frames. Feel free to add or change the values in the
rotations array.  By default, we interpolate between each key frame in 1 second
intervals.

We will implement 3 interpolation methods, `getModelMatrixLerp`,
`getModelMatrixEuler`, and `getModelMatrixQuat`. Each method takes in two
vectors `from` and `to` that represent Euler angles and `t`, a floating point
value from 0 to 1 that represents the proportion of the way through the current
rotation.

## Part 1 - Interpolation of matrices

You just about NEVER want to directly interpolate transformation matrices. This
part is intended to show you why.  (Hint, each vector that makes up the matrix
is interpolated, which can result in a skewed and scaled intermediate space.)

In the `getModelMatrixLerp`, construct two matrices, one that represents the
‘from’ orientation and one that represents the ‘to’ orientation. Use the ‘t’
variable to perform an element-wise linear interpolation.  Updating
`getModelMatrixLerp` will change the model matrix of one of three cubes. In the
following parts, we’ll animate the other two using different techniques.

## Part 2 - Interpolation of Euler angles

In this step, you need to use ‘from’, ‘to’ and ‘t’ to interpolate Euler angles.
Interpolate the angles and then convert to a 4x4 matrix.  Modifying this methods
will update the orientation of another cube.

## Part 3 - Spherical linear interpolation of quaternions

Finally, you will convert the ‘from’ and ‘to’ variables to quaternions before
performing any interpolation. glm provides a quaternion data structure called
quat. You can construct a quaternion using Euler angles by passing the
constructor a vec3. Quaternions can be interpolated using spherical linear
interpolation, also known as slerp.  Spherical linear interpolation is similar
to linear interpolation as it takes a value between 0 and 1 to combine two other
values. In the case of quaternions, it returns a combined orientation along the
shortest path between them. Use the `glm::slerp` function to combine your
quaternions using the ‘t’ variable.  The last step is to convert the resulting
quaternion into a 4x4 matrix that can be used by our vertex shader. Use
`glm::toMat4` go back to a 4x4 matrix.  Returning this matrix will animation the
third cube.

## Things to notice

Linearly interpolating transform matrices is a bad idea as the interpolated
matrix will have strange scaling and skewing.

Animating Euler angles is the standard way to animate orientation. Conceptually,
it is easy to grasp and can be used to spin objects around multiple times.
Gimbal lock can be a serious problem, though, so animators must watch out for
those situations. You can notice the effects of gimbal lock if you rotate about
Y 90 degrees. After doing so, notice how changing the X or Z rotation results in
a rotation about the same axis.

Quaternions do not inherently suffer from gimbal lock, but as Euler angles are
commonly what orientation is input as you still must be aware that it can be a
problem.

When animating between quaternions, notice how the shortest path is taken,
whereas with Euler angles it can take a much longer path.

There are no quaternion operations implemented in GLSL, so if you want to use
them in a vertex or fragment shader you’d need to implement them yourself (or
find them online).
