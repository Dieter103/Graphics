#ifndef _CSCI441_SHAPE_H_
#define _CSCI441_SHAPE_H_

#include <cstdlib>
#include <vector>

template <typename T, typename N, typename C>
void add_vertex(T& coords, const N& x, const N& y, const N& z,
        const C& r, const C& g, const C& b,
        const Vector& n=Vector(1,0,0), bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/100.;
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

template <typename T>
Vector face_normal(
        const T& alpha_x, const T& alpha_y, const T& alpha_z,
        const T& beta_x, const T& beta_y, const T& beta_z,
        const T& gamma_x, const T& gamma_y, const T& gamma_z) {
    Vector alpha(alpha_x, alpha_y, alpha_z);
    Vector beta(beta_x, beta_y, beta_z);
    Vector gamma(gamma_x, gamma_y, gamma_z);
    return ((beta-alpha).cross(gamma-alpha)).normalized();
}

class DiscoCube {
public:
    std::vector<float> coords;
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
    } {}

};

class Cylinder {
public:
    std::vector<float> coords;
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

            // for normals, we are computing use the face noral at each vertex.
            // this will create faciting, but it is ok for a first pass.

            // add triangle viL, viH, vip1L
            Vector nt0 = face_normal(
                    vi_x, -h, vi_y,
                    vi_x, h, vi_y,
                    vip1_x, -h, vip1_y);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b, nt0);
            add_vertex(coords, vi_x, h, vi_y, r, g, b, nt0);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b, nt0);

            // add triangle vip1L, viH, vip1H
            Vector nt1 = face_normal(
                    vip1_x, -h, vip1_y,
                    vi_x, h, vi_y,
                    vip1_x, h, vip1_y);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b, nt1);
            add_vertex(coords, vi_x, h, vi_y, r, g, b, nt1);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b, nt1);

            // add high triangle vi, vip1, 0
            Vector nh(0, 1, 0);
            add_vertex(coords, vip1_x, h, vip1_y, r, g, b, nh);
            add_vertex(coords, vi_x, h, vi_y, r, g, b, nh);
            add_vertex(coords, c_x, h, c_y, r, g, b, nh);

            // // add low triangle vi, vip1, 0
            Vector nl(0, -1, 0);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b, nl);
            add_vertex(coords, c_x, -h, c_y, r, g, b, nl);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b, nl);
        }
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

            // use face noral for the top, this will create faceting,
            // but it is ok for a quick first approximation
            Vector n_high = face_normal(
                    vi_x, -h, vi_y,
                    c_x, h, c_y,
                    vip1_x, -h, vip1_y);

            // add triangle viL, viH, vip1L
            add_vertex(coords, vi_x, -h, vi_y, r, g, b, n_high);
            add_vertex(coords, c_x, h, c_y, r, g, b, n_high);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b, n_high);

            // // add low triangle vi, vip1, 0
            Vector n_low(0,-1,0);
            add_vertex(coords, vip1_x, -h, vip1_y, r, g, b, n_low);
            add_vertex(coords, c_x, -h, c_y, r, g, b, n_low);
            add_vertex(coords, vi_x, -h, vi_y, r, g, b, n_low);
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
                Vector nij(vij_x, vij_y, vij_z);

                // vertex i+1,j
                double vip1j_x = x(radius, phi_ip1, theta_j);
                double vip1j_y = y(radius, phi_ip1, theta_j);
                double vip1j_z = z(radius, phi_ip1, theta_j);
                Vector nip1j(vip1j_x, vip1j_y, vip1j_z);

                // vertex i,j+1
                double vijp1_x = x(radius, phi_i, theta_jp1);
                double vijp1_y = y(radius, phi_i, theta_jp1);
                double vijp1_z = z(radius, phi_i, theta_jp1);
                Vector nijp1(vijp1_x, vijp1_y, vijp1_z);

                // vertex i+1,j+1
                double vip1jp1_x = x(radius, phi_ip1, theta_jp1);
                double vip1jp1_y = y(radius, phi_ip1, theta_jp1);
                double vip1jp1_z = z(radius, phi_ip1, theta_jp1);
                Vector nip1jp1(vip1jp1_x, vip1jp1_y, vip1jp1_z);

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, nij);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, nip1j);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, nijp1);

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, nijp1);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, nip1jp1);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, nip1j);
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

    Vector normal(float c, float a, float phi, float theta) {
        // Normal calculation adapted from:
        // http://web.cs.ucdavis.edu/~amenta/s12/findnorm.pdf
        Vector t(-sin(phi), cos(phi), 0);
        Vector s(cos(phi)*-sin(theta), sin(phi)*-sin(theta), cos(theta));
        return t.cross(s).normalized();
    }

public:
    std::vector<float> coords;
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
                Vector nij = normal(c, a, phi_i, theta_j);

                // vertex i+1,j
                double vip1j_x = x(c, a, phi_ip1, theta_j);
                double vip1j_y = y(c, a, phi_ip1, theta_j);
                double vip1j_z = z(c, a, phi_ip1, theta_j);
                Vector nip1j = normal(c, a, phi_ip1, theta_j);

                // vertex i,j+1
                double vijp1_x = x(c, a, phi_i, theta_jp1);
                double vijp1_y = y(c, a, phi_i, theta_jp1);
                double vijp1_z = z(c, a, phi_i, theta_jp1);
                Vector nijp1 = normal(c, a, phi_i, theta_jp1);

                // vertex i+1,j+1
                double vip1jp1_x = x(c, a, phi_ip1, theta_jp1);
                double vip1jp1_y = y(c, a, phi_ip1, theta_jp1);
                double vip1jp1_z = z(c, a, phi_ip1, theta_jp1);
                Vector nip1jp1 = normal(c, a, phi_ip1, theta_jp1);

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, nij);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, nip1j);
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, nijp1);

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, nijp1);
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, nip1jp1);
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, nip1j);
            }
        }
    }

};

#endif
