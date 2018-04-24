# Computer Graphics CSCI 441

**NOTE: This is a live document and is subject to change throughout the
semester.**

Computer graphics is a field of computer science that involves generating visual
content.  Applications of computer graphics includes modeling and animation
software, CAD design software, image manipulation packages such as Photoshop or
Illustrator, video games, medical visualisation tools and much, much more. In
this class, we will cover some of the fundamentals of computer graphics; from
transformations and camera projections, to light and shading models, to
simulations that approximate phenomena in the real world. We will use C++ and
OpenGL to explore practical, realtime, graphics programming while learning the
theory behind it so you can apply it to other environments.

## Assignments

Class will be a mix of lecture and in class lab assignments.  There will be many
lab assignments that are designed to give you a better understanding of the
topics taught in lecture. Code will be provided to get you up and running with
the labs. You may work in groups of two or three.  You must demo your labs to me
in class or office hours and push your code up to Bitbucket in a repository
you've shared with me prior to class on the due date.  There will also be a few
major programming assignments as well. The program assignments will take
significantly more time than the labs and are designed to inspire individual
creativity and self expression. I’ll try to keep lectures as short as possible
to give you time in class to work on your assignments with me available to ask
questions.  All assignments and other resources for the class will be made
available via Bitbucket:

https://bitbucket.org/msu-cs/csci441-spring2018

## Meeting Times

Tuesdays and Thursdays 15:05 - 16:20 in Barnard Hall 108.

## Instructor

David L. Millman, Ph.D.

**Email**: david.millman@montana.edu

**Office hours**: Mon 17:00 - 18:00 and Thurs 12:00 - 13:00

**Bitbucket username**: david_millman

## Grader

Amy Peerlinck

**Email**: amy.peerlinck@student.montana.edu

**Bitbucket username**: amy_linck
## Textbook

Textbooks are optional but recommended

* [Fundamentals of Computer Graphics, 4th Edition](https://www.amazon.com/Fundamentals-Computer-Graphics-Fourth-Marschner/dp/1482229390),
(FoCG in recommended reading below).
* [OpenGL Programming Guide, 9th Edition](https://www.amazon.com/OpenGL-Programming-Guide-Official-Learning/dp/0134495497)
(referred to as GL Guide in recommended reading below).
* [Computational Geometry: Algorithms and Applications 3rd Edition](https://link-springer-com.proxybz.lib.montana.edu:3443/book/10.1007/978-3-540-77974-2)
(DutchBook in the recommended reading below, book is available online through
the MSU library)

## Online Resources

* [OpenGL Reference Pages](https://www.opengl.org/sdk/docs/man/)
* [Learn OpenGL Website](https://learnopengl.com/)(referred to as LoGL in recommended reading below)
* [C++ Documentation](http://www.cplusplus.com/doc/tutorial/)

## Class schedule

The lecture schedule is subject to change throughout the semester, but here is
the current plan. Assignments and due dates will be updated as they're assigned in class.

### January

| Date | Description                                                         | Assigned                       | Due                            | Recommended Reading                        |
|------|---------------------------------------------------------------------|--------------------------------|--------------------------------|--------------------------------------------|
| 1/11 | [Intro - applications of computer graphics](./notes/01-11.pdf)      | [Lab 0](./labs/lab0/README.md) |                                | FoCG Chapter 1                             |
| 1/16 | C++ overview / git basics                                           |                                |                                |                                            |
| 1/18 | [Rasterization / Barycentric coordinates / Color](./notes/01-18.pdf)| [Lab 1](./labs/lab1/README.md) | [Lab 0](./labs/lab0/README.md) | FoCG 2.7.1, 3.3                            |
| 1/23 | [Barycentric coordinates](./notes/01-23.pdf)                        |                                |                                | FoCG 8.1.2                                 |
| 1/25 | [Overview of graphics pipeline](./notes/01-25.pdf)                  | [Lab 2](./labs/lab2/README.md) | [Lab 1](./labs/lab0/README.md) | GL Chapter 1, LoGL "Hello Tri"             |
| 1/30 | [Vectors / Coordinates / OpenGL basics](./notes/01-30.pdf)          |                                |                                | FoCG 2, LoGL "Hello Window" & "Hello Tri"  |

### February

| Date     | Description                                               | Assigned                                   | Due                             | Recommended Reading               |
|----------|-----------------------------------------------------------|--------------------------------------------|---------------------------------|-----------------------------------|
| 2/1      | [OpenGL basics](./notes/02-01.pdf)                        |                                            |                                 | LoGL "Hello Tri"                  |
| 2/6      | [Matrices, Rotation and Scale](./notes/02-06.pdf)         | [Lab 3](./labs/lab3/README.md)             | [Lab 2](./labs/lab2/README.md)  | FoCG 6.1                          |
| 2/8      | [Affine Transformations](./notes/02-08.pdf)               |                                            |                                 | FoCG 6.3                          |
| 2/13     | [Coordinate Transformations](./notes/02-13.pdf)           | [Lab 4](./labs/lab4/README.md)             | [Lab 3](./labs/lab3/README.md)  | FoCG 6.5, 4.2                     |
| 2/15     | [Projections](./notes/02-15.pdf)                          |                                            |                                 | FoCG 7.0-.1                       |
| 2/20     | [Projections, Camera](./notes/02-20.pdf)                  | [Program 1](./programs/program1/README.md) |                                 | FoCG 7.1-7.2                      |
| 2/22     | [Diffuse Shading](./notes/02-22.pdf)                      |                                            | [Lab 4](./labs/lab4/README.md)  | FoCG 10.1                         |
| 2/27     | [Triangulation/Transforming Normals](./notes/02-27.pdf)   | [Lab 5](./labs/lab5/README.md)             |                                 | FoCG 6.2.2, [David Eberly's trianguation notes](https://www.geometrictools.com/Documentation/TriangulationByEarClipping.pdf)|

### March

| Date     | Description                                                    | Assigned                                  | Due                                               | Recommended Reading |
|----------|----------------------------------------------------------------|---------------------------------------    |---------------------------------------------------|---------------------|
| 3/1      | [Standard Template Library/Phong Shading](./notes/03-01.pdf)   |                                           |                                                   | FoCG 10.2, [Geeks for Geeks STL Notes](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/)|
| 3/6      | [Problem Session](./notes/03-06.pdf)                           |                                           | [Lab5](./labs/lab5/README.md)(anywhere on earth)  |                     |
| 3/8      | Midterm                                                        | [Program 2](./programs/program2/README.md)|                                                   |                     |
| 3/11     | No class (due date, any where on earth)                        |                                           | [Program 1](./programs/program1/README.md)        |                     |
| 3/13     | No class (Spring Break)                                        | [Lab EC 1](./labs/lab-ec1/README.md)      |                                                   |                     |
| 3/15     | No class (Spring Break)                                        |                                           |                                                   |                     |
| 3/20     | [Polygon Soup / Element Arrays](./notes/03-20.pdf)             | [Lab 6](./labs/lab6/README.md)            | [Lab EC 1](./labs/lab-ec1/README.md)              | FoCG 12.1           |
| 3/22     | Doubly Connected Edge List                                     |                                           |                                                   | DutchBook 2.2       |
| 3/27     | [Texture Mapping](./notes/03-27.pdf)                           |                                           | [Lab 6](./labs/lab6/README.md)                    | FoCG 11.1-.2        |
| 3/29     | [Texture Mapping Pt 2](./notes/03-29.pdf)                      | [Lab 7](./labs/lab7/README.md)            |                                                   | FoCG 11.2-.3        |

### April

| Date     | Description                                    | Assigned                                      | Due                                           | Recommended Reading |
|----------|------------------------------------------------|-----------------------------------------------|-----------------------------------------------|---------------------|
| 4/3      | [Texture Mapping in OpenGL](./notes/04-03.pdf) |                                               |                                               | LoGL "Textures"     |
| 4/5      | [Ray Tracing](./notes/04-05.pdf)               | [Program 3](./programs/program3/README.md)    | [Program 2](./programs/program2/README.md)    | FoCG 4.1,.3         |
| 4/10     | Computing View Rays                            | [Lab 8](./labs/lab8/README.md)                | [Lab 7](./labs/lab7/README.md)                | FoCG 4.3            |
| 4/12     | [Computing Intersections](./notes/04-12.pdf)   |                                               |                                               | FoCG 4.4            |
| 4/17     | Quaternions                                    | [Lab 9](./labs/lab9/README.md)                | [Lab 8](./labs/lab8/README.md)                | FoCG 16.2           |
| 4/19     | Spatial Data Structures                        |                                               |                                               | FoCG 12.3           |
| 4/24     | Where to go next                               |                                               | [Lab 9](./labs/lab9/README.md)                |                     |
| 4/26     | Review/Wrap up                                 |                                               | [Program 3](./programs/program3/README.md)    |                     |

### May

| Date     | Description                                 |
|----------|---------------------------------------------|
| 5/4      | Final - 12-1:50pm                           |


## Catalog Information

PREREQUISITE: M 221 and CSCI 232. High resolution computer graphics. 3D graphics
programming using a high level API. Vector mathematics for graphics. Graphics
primitives.  Curve and surface representations. Transformations using matrices
and quaternions.  Representing natural objects with particle systems and
fractals. Shading and lighting models.  Global illumination models. Color
representations.

## Course Offerings

At the end of the course, students should be able to

* Write basic graphical applications using OpenGL and C++
* Understand the modern graphics pipeline and how to leverage hardware to write
  realtime graphics applications
* Use vectors and matrices to transform geometry in 3D space
* Understand common shading and lighting models for displaying 3D models
* Use particle systems to simulate real world phenomena.

## Course Evaluation

* Participation 5%
* Labs 20%
* Programs 40%
* Midterm 15%
* Final 20%

## Discussion Board

Group discussions, questions, and announcements will take place using
Brightspace.  It is OK to send me an email if you have a question that you feel
is not appropriate to share with the class.  If, however, you send me an email
with a question for which the response would be useful to the rest of the class,
I will likely ask you to post it.

## Policy on Collaboration and Academic Misconduct

Collaboration IS encouraged, however, all submitted individual work must be your
own and you must acknowledge your collaborators at the beginning of the
submission.

On any group project, every team member is expected to make a substantial
contribution. The distribution of the work, however, is up to the team.

A few specifics for the assignments.  You may:

* Work with the other people on your team.
* Share ideas with other teams.
* Help other teams debug their code.

You may NOT:

* Share code that you wrote with other teams.
* Submit code that someone on your team did not write.
* Modify another's code and claim it as your own.

Using resources in addition to the course materials is encouraged. But, be sure
to properly cite additional resources. Remember, it is NEVER acceptable to pass
others work off as your own.

Paraphrasing or quoting another’s work without citing the source is a form of
academic misconduct. Even inadvertent or unintentional misuse or appropriation
of another’s work (such as relying heavily on source material that is not
acknowledged) is considered plagiarism. If you have any questions about using
and citing sources, you are expected to ask for clarification. My rule of thumb
is if I am in doubt, I cite.

By participating in this class, you agree to abide by the [student code of
conduct](http://www.montana.edu/policy/student_conduct/).  Please review the
policy.

## Policy on Assignments

All assignments must be submitted by the start of class on the due date. Late
assignments will not be accepted.

For descriptive assignments and reports, the submission should be typed up and
submitted as a PDF (LaTeX suggested but not required). For code assignments,
well organized source code with clear comments should be submitted.

## Policy on Class Attendance

Class attendance is required. If a student must miss a class, please notify me
as soon as possible. Note that class participation is part of your final grade.
If you do not show up you cannot participate.

## Classroom Etiquette

Except for note taking and coding, please keep electronic devices off during
class, they can be distractions to other students. Disruptions to the class will
result in you being asked to leave the lecture and will negatively impact your
grade.

## Special needs information

If you have a documented disability for which you are or may be requesting an
accommodation(s), you are encouraged to contact me and Disabled
Student Services as soon as possible.
