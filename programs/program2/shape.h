#ifndef _CSCI441_SHAPE_H_
#define _CSCI441_SHAPE_H_

#include <cstdlib>
#include <vector>
#include <csci441/vector.h>
#include <map>

template <typename T, typename N, typename C>

void add_vertex(T& coords, const N& x, const N& y, const N& z,
        const C& r, const C& g, const C& b,
        const Vector& n=Vector(1,0,0), bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/1000.;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    coords.push_back(r*noise);
    coords.push_back(g*noise);
    coords.push_back(b*noise);

    Vector normal = n.normalized();
    coords.push_back(normal.x());
    coords.push_back(normal.y());
    coords.push_back(normal.z());
}

std::vector<float> calcFaceNormals(std::vector<float> coords){

    for(int i = 0; i<coords.size(); i+=27){
        Vector v1 = Vector(coords.at(i), coords.at(i+1), coords.at(i+2));
        Vector v2 = Vector(coords.at(i+9), coords.at(i+10), coords.at(i+11)) - v1;
        Vector v3 = Vector(coords.at(i+18), coords.at(i+19), coords.at(i+20)) - v1;
        Vector norm = v2.cross(v3);
//        norm = Vector(0,0,0);

        Vector norm1 = v2.cross(v1);
        norm = norm.normalized();

        coords.at(i+6) = norm.x();
        coords.at(i+7) = norm.y();
        coords.at(i+8) = norm.z();
        coords.at(i+15) = norm.x();
        coords.at(i+16) = norm.y();
        coords.at(i+17) = norm.z();
        coords.at(i+24) = norm.x();
        coords.at(i+24) = norm.y();
        coords.at(i+26) = norm.z();
    }
//    for(int i = 27; i<coords.size(); i+=54){
//        Vector v3 = Vector(coords.at(i+18), coords.at(i+19), coords.at(i+20));
//        Vector v1 = Vector(coords.at(i), coords.at(i+1), coords.at(i+2)) -v3;
//        Vector v2 = Vector(coords.at(i+9), coords.at(i+10), coords.at(i+11)) - v3;
//
//        Vector norm = v2.cross(v1);
////        norm = Vector(0,0,0);
//        Vector norm1 = v2.cross(v1);
//        norm = norm.normalized();
//
//        coords.at(i+6) = norm.x();
//        coords.at(i+7) = norm.y();
//        coords.at(i+8) = norm.z();
//        coords.at(i+15) = norm.x();
//        coords.at(i+16) = norm.y();
//        coords.at(i+17) = norm.z();
//        coords.at(i+24) = norm.x();
//        coords.at(i+24) = norm.y();
//        coords.at(i+26) = norm.z();
//    }


    return coords;
}

//std::map<int, vector<Vector>>::iterator searchByValue(map<int, vector<Vector>> & vertices, Vector val)
//{
//    // Iterate through all elements in std::map and search for the passed element
//    std::map<int, vector<Vector>>::iterator it = vertices.begin();
//    while(it != vertices.end())
//    {
//        if(it->second.at(0) == val)
//            return it;
//        it++;
//    }
//}

std::vector<float> calcVertexNormals(std::vector<float> coords){
    std::vector<Vector> vertices;
    std::map<std::vector<float>, std::vector<float>> normals;
//    std::map<int, std::vector<Vector>>::iterator it = vertices.begin();
    std::vector<float> zero;
    zero.push_back(0);
    zero.push_back(0);
    zero.push_back(0);

    //grabbing all vertices and mapping them to a normal
    for (int j = 0; j < coords.size() ; j+=9) {
        std::vector<float> vertex;
        vertex.push_back(coords.at(j));
        vertex.push_back(coords.at(j+1));
        vertex.push_back(coords.at(j+2));


        normals.insert(std::make_pair(vertex,zero));
        vertices.push_back(Vector(vertex.at(0), vertex.at(1), vertex.at(2)));

    }

    for(int i = 0; i<vertices.size(); i+=3){
        Vector v1 = vertices.at(0+i);
        Vector v2 = vertices.at(1+i);
        Vector v3 = vertices.at(2+i);

        std::vector<float> vertex1;
        vertex1.push_back(v1.x());
        vertex1.push_back(v1.y());
        vertex1.push_back(v1.z());

        std::vector<float> vertex2;
        vertex2.push_back(v2.x());
        vertex2.push_back(v2.y());
        vertex2.push_back(v2.z());

        std::vector<float> vertex3;
        vertex3.push_back(v3.x());
        vertex3.push_back(v3.y());
        vertex3.push_back(v3.z());


        Vector norm1 = (v1-v3).cross(v2-v1);
        Vector norm2 = (v2-v3).cross(v2-v1);
        Vector norm3 = (v3-v1).cross(v3-v2);

//        Vector oldNorm1 = Vector(normals[vertex1].x(), normals[vertex1].y(), normals[vertex1].z());

//        std::cout<< float(normals[vertex1].x()) <<std::endl;
        std::map<std::vector<float>, std::vector<float>>::iterator it = normals.find(vertex1);
//        if (it != normals.end()){std::cout<< "found" <<std::endl;
//            it->second = Vector(0,0,0);
//        }

//

        normals[vertex1].at(0) = normals[vertex1].at(0) + norm1.x();
        normals[vertex1].at(1) = normals[vertex1].at(1) + norm1.y();
        normals[vertex1].at(2) = normals[vertex1].at(2) + norm1.z();

        normals[vertex2].at(0) = normals[vertex2].at(0) + norm2.x();
        normals[vertex2].at(1) = normals[vertex2].at(1) + norm2.y();
        normals[vertex2].at(2) = normals[vertex2].at(2) + norm2.z();

        normals[vertex3].at(0) = normals[vertex3].at(0) + norm3.x();
        normals[vertex3].at(1) = normals[vertex3].at(1) + norm3.y();
        normals[vertex3].at(2) = normals[vertex3].at(2) + norm3.z();
//        normals[vertex2] = normals[vertex2] - norm2;
//        normals[vertex3] = normals[vertex3] - norm3;
    }

    for (int i = 0; i < coords.size() ; i+=9) {

        std::vector<float> vertex;
        vertex.push_back(coords.at(i+0));
        vertex.push_back(coords.at(i+1));
        vertex.push_back(coords.at(i+2));
        Vector normalized = Vector(normals[vertex].at(0), normals[vertex].at(1), normals[vertex].at(2)).normalized();
//        std::vector<float> newNormal;

        coords.at(i+6) = normalized.x();
        coords.at(i+7) = normalized.y();
        coords.at(i+8) = normalized.z();



    }


    return coords;
}

class DiscoCube {
public:
    std::vector<float> coords;
    std::vector<float> faceNormCoords;
    std::vector<float> vertexNormCoords;
    DiscoCube() : coords{
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0,

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0
    } {
        faceNormCoords = calcFaceNormals(coords);
        vertexNormCoords = calcVertexNormals(coords);
    }


};

class Cylinder {
public:
    std::vector<float> coords;
    std::vector<float> faceNormCoords;
    std::vector<float> vertexNormCoords;

    Cylinder(unsigned int n, float r, float g, float b) {
        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);


            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);




            // add triangle vip1L, viH, vip1H
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b);

            // add high triangle vi, vip1, 0
            Vector nh(0, 1, 0);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b);
            add_vertex(coords, vi_x, h, vi_y, r, g, b);
            add_vertex(coords, c_x, h, c_y, r, g, b);

            // // add low triangle vi, vip1, 0
            Vector nl(0, -1, 0);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, c_x, -h, c_y, r, g, b);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
        }   vertexNormCoords = calcVertexNormals(coords);
        faceNormCoords = calcFaceNormals(coords);
    }
};


class Cone {
public:
    std::vector<float> coords;
    Cone(unsigned int n, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            // add triangle viL, viH, vip1L
            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
            add_vertex(coords, c_x, h, c_y, r, g, b);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);

            // // add low triangle vi, vip1, 0
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b);
            add_vertex(coords, c_x, -h, c_y, r, g, b);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b);
        }
    }
};

class Sphere {
    double x(float r, float phi, float theta){
        return r*cos(theta)*sin(phi);
    }

    double y(float r, float phi, float theta){
        return r*sin(theta)*sin(phi);
    }

    double z(float r, float phi, float theta){
        return r*cos(phi);
    }

public:
    std::vector<float> coords;
    Sphere(unsigned int n, float radius, float r, float g, float b) {
        int n_steps = (n%2==0) ? n : n+1;
        double step_size = 2*M_PI / n_steps;

        for (int i = 0; i < n_steps/2.0; ++i) {
            for (int j = 0; j < n_steps; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n_steps)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n_steps)*step_size;

                // vertex i,j
                double vij_x = x(radius, phi_i, theta_j);
                double vij_y = y(radius, phi_i, theta_j);
                double vij_z = z(radius, phi_i, theta_j);

                // vertex i+1,j
                double vip1j_x = x(radius, phi_ip1, theta_j);
                double vip1j_y = y(radius, phi_ip1, theta_j);
                double vip1j_z = z(radius, phi_ip1, theta_j);

                // vertex i,j+1
                double vijp1_x = x(radius, phi_i, theta_jp1);
                double vijp1_y = y(radius, phi_i, theta_jp1);
                double vijp1_z = z(radius, phi_i, theta_jp1);

                // vertex i+1,j+1
                double vip1jp1_x = x(radius, phi_ip1, theta_jp1);
                double vip1jp1_y = y(radius, phi_ip1, theta_jp1);
                double vip1jp1_z = z(radius, phi_ip1, theta_jp1);

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b);

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b);
            }
        }
    }
};

class Torus {
    double x(float c, float a, float phi, float theta) {
        return (c+a*cos(theta))*cos(phi);
    }

    double y(float c, float a, float phi, float theta) {
        return (c+a*cos(theta))*sin(phi);
    }

    double z(float c, float a, float phi, float theta) {
        return a*sin(theta);
    }

public:
    std::vector<float> coords;
    std::vector<float> faceNormCoords;
    std::vector<float> vertexNormCoords;




    Torus(unsigned int n, float c, float a, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n)*step_size;

                // vertex i,j
                double vij_x = x(c, a, phi_i, theta_j);
                double vij_y = y(c, a, phi_i, theta_j);
                double vij_z = z(c, a, phi_i, theta_j);

                // vertex i+1,j
                double vip1j_x = x(c, a, phi_ip1, theta_j);
                double vip1j_y = y(c, a, phi_ip1, theta_j);
                double vip1j_z = z(c, a, phi_ip1, theta_j);

                // vertex i,j+1
                double vijp1_x = x(c, a, phi_i, theta_jp1);
                double vijp1_y = y(c, a, phi_i, theta_jp1);
                double vijp1_z = z(c, a, phi_i, theta_jp1);

                // vertex i+1,j+1
                double vip1jp1_x = x(c, a, phi_ip1, theta_jp1);
                double vip1jp1_y = y(c, a, phi_ip1, theta_jp1);
                double vip1jp1_z = z(c, a, phi_ip1, theta_jp1);

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b);

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b);
            }
        }
        faceNormCoords = calcFaceNormals(coords);
        vertexNormCoords = calcVertexNormals(coords);
    }

};

#endif
