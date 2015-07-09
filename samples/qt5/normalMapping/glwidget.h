#ifndef __GLWIDGET__
#define __GLWIDGET__

#include <utils/qttrackballwidget.hpp>
#include <phongshader.hpp>
#include <normalmapping.hpp>
#include <texture.hpp>
#include <bumpmesh.hpp>


class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT

public:

	explicit GLWidget(QWidget *parent);
	~GLWidget();
    
    /**
     * @brief Initializes the shader effect
     * @todo remove hard coded mesh file!!
     */
    void initializeGL();

    /**
     * Repaints screen buffer.
     **/
    virtual void paintGL();

	
	void increaseLightIntensity() { normalMapping.increaseLightIntensity(); };
	void decreaseLightIntensity() { normalMapping.decreaseLightIntensity(); };

private:

	void loadTextures();

	/// Texture to hold diffuse texture
	Tucano::Texture* diffuse_map;

	/// Texture to hold normal texture
	Tucano::Texture* normal_map;

	/// Texture to hold specular texture
	Tucano::Texture* specular_map;

	/// A simple normal mapping shader for rendering meshes
	Effects::NormalMapping normalMapping;

	Tucano::BumpMesh bumpMesh;

	GLuint VertexArrayID;
	
	std::vector<Eigen::Vector3f> vertices;
	std::vector<Eigen::Vector2f> uvs;
	std::vector<Eigen::Vector3f> normals;
	std::vector<Eigen::Vector3f> tangents;
	std::vector<Eigen::Vector3f> bitangents;
	std::vector<unsigned short> indices;
	std::vector<Eigen::Vector3f> indexed_vertices;
	std::vector<Eigen::Vector2f> indexed_uvs;
	std::vector<Eigen::Vector3f> indexed_normals;
	std::vector<Eigen::Vector3f> indexed_tangents;
	std::vector<Eigen::Vector3f> indexed_bitangents;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;
	GLuint elementbuffer;

};

#endif // GLWIDGET
