/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_quad.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "..\include\geometry_custom_cube.h"


namespace EDK3 {

	//IMPORTANT!!!
	//TODO constructors, destructor and =operator here!!!

	CubeCustom::CubeCustom()
	{
		is_initialized_ = false;
	}
	CubeCustom::~CubeCustom() {}
	CubeCustom& CubeCustom::operator=(const CubeCustom&)
	{
		return *this;
	}

	void CubeCustom::init8v(const float cube_size)
	{
		EDK3::dev::GPUManager::Instance()->newBuffer(&elements_buffer);
		EDK3::dev::GPUManager::Instance()->newBuffer(&order_buffer);

		float size = cube_size * 0.5f;
		ESAT::Vec3 positions[] =
		{
			//front face
			{-size, -size, size},
			{-size, +size, size},
			{+size, +size, size},
			{+size, -size, size},

			//back face
			{+size, -size, -size},
			{+size, +size, -size},
			{-size, +size, -size},
			{-size, -size, -size},
		};

		ESAT::Vec3 normals[] =
		{
			//v0
			{+0.0f, +0.0f, +1.0f},
			{-1.0f, +0.0f, +0.0f},
			{+0.0f, -1.0f, +0.0f},

			//v1
			{+0.0f, +0.0f, +1.0f},
			{-1.0f, +0.0f, +0.0f},
			{+0.0f, +1.0f, +0.0f},

			//v2
			{+0.0f, +0.0f, +1.0f},
			{+1.0f, +0.0f, +0.0f},
			{+0.0f, +1.0f, +0.0f},

			//v3
			{+0.0f, +0.0f, +1.0f},
			{+1.0f, +0.0f, +0.0f},
			{+0.0f, -1.0f, +0.0f},

			//v4
			{+0.0f, +0.0f, -1.0f},
			{+1.0f, +0.0f, +0.0f},
			{+0.0f, -1.0f, +0.0f},

			//v5
			{+0.0f, +0.0f, -1.0f},
			{+1.0f, +0.0f, +0.0f},
			{+0.0f, +1.0f, +0.0f},

			//v6
			{+0.0f, +0.0f, -1.0f},
			{-1.0f, +0.0f, +0.0f},
			{+0.0f, +1.0f, +0.0f},

			//v7
			{+0.0f, +0.0f, -1.0f},
			{-1.0f, +0.0f, +0.0f},
			{+0.0f, -1.0f, +0.0f},
		};

		ESAT::Vec2 uvs[] =
		{
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f},

			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f},

		};
		constexpr int kNData = 8 * 4 * 2;
		float data[kNData];
		int j = 0;
		for (int i = 0; i < 8; i++)
		{
			data[j++] = positions[i].x;
			data[j++] = positions[i].y;
			data[j++] = positions[i].z;

			data[j++] = normals[i].x;
			data[j++] = normals[i].y;
			data[j++] = normals[i].z;

			data[j++] = uvs[i].x;
			data[j++] = uvs[i].y;
		}
		elements_buffer->init(sizeof(data));
		elements_buffer->uploadData(data, sizeof(data), 0);

		unsigned int order[] = {
			//Front face
			0, 3, 1, 1, 3, 2,
			//Right face
			3, 4, 2, 2, 4, 5,
			//Back face
			4, 7, 5, 5, 7, 6,
			//Left face
			7, 0, 6, 6, 0, 1,
			//Top face
			1, 2, 6, 6, 2, 5,
			//Bottom face
			7, 4, 0, 0, 4, 3
		};
		order_buffer->init(sizeof(order));
		order_buffer->uploadData(order, sizeof(order), 0);
	}
	void CubeCustom::init24v(const float cube_size)
	{
		EDK3::dev::GPUManager::Instance()->newBuffer(&elements_buffer);
		EDK3::dev::GPUManager::Instance()->newBuffer(&order_buffer);

		float size = cube_size * 0.5f;
		ESAT::Vec3 positions[] =
		{
			//Frontal face
			{-size, -size, size},
			{-size, size, size},
			{size, size, size},
			{size, -size, size},

			//Right face
			{size, -size, size},
			{size, size, size},
			{size, size, -size},
			{size, -size, -size},

			//Back face
			{size, -size, -size},
			{size, size, -size},
			{-size, size, -size},
			{-size, -size, -size},

			//Left face
			{-size, -size, -size},
			{-size, size, -size},
			{-size, size, size},
			{-size, -size, size},

			//Top face
			{-size, size, size},
			{-size, size, -size},
			{size, size, -size},
			{size, size, size},

			//Bottom face
			{-size, -size, -size},
			{size, -size, -size},
			{size, -size, size},
			{-size, -size, size},

		};

		ESAT::Vec3 normals[] =
		{
			//Front face
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},

			//Right face
			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},

			//Back face
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},

			//Left face
			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},
			//Top face
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},

			//Bottom face
			{0.0f,-1.0f,0.0f},
			{0.0f,-1.0f,0.0f},
			{0.0f,-1.0f,0.0f},
			{0.0f,-1.0f,0.0f},
		};

		ESAT::Vec2 uvs[] =
		{
			//Front face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},

			//Right face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},

			//Back face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},

			//Left face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},

			//Top face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},
			//Bottom face
			{0.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f},
			{1.0f,0.0f},
		};
		constexpr int kNData = 8 * 4 * 6;
		float data[kNData];
		int j = 0;
		for (int i = 0; i < 24; i++)
		{
			data[j++] = positions[i].x;
			data[j++] = positions[i].y;
			data[j++] = positions[i].z;

			data[j++] = normals[i].x;
			data[j++] = normals[i].y;
			data[j++] = normals[i].z;

			data[j++] = uvs[i].x;
			data[j++] = uvs[i].y;
		}

		elements_buffer->init(sizeof(data));
		elements_buffer->uploadData(data, sizeof(data), 0);

		unsigned int order[] = {
			//Front face
			0, 3, 1, 1, 3, 2,
			//Right face
			4, 7, 5, 5, 7, 6,
			//Back face
			8, 11, 9, 9, 11, 10,
			//Left face
			12, 15, 13, 13, 15, 14,
			//Top face
			16, 19, 17, 17, 19, 18,
			//Bottom face
			20, 23, 21, 21, 23, 22
		};
		order_buffer->init(sizeof(order));
		order_buffer->uploadData(order, sizeof(order), 0);
	}

	bool CubeCustom::bindAttribute(const Attribute a,
		unsigned int where_to_bind_attribute) const {
		//TODO
		//EDK3::dev::GPUManager::Instance()->enableVertexAttribute
		switch (a)
		{
		case Attribute::A_POSITION:
			EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
				elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, 0,
				sizeof(float) * 0.0f, sizeof(float) * 8.0f);
			break;
		case Attribute::A_NORMAL:
			EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
				elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, 0,
				sizeof(float) * 3.0f, sizeof(float) * 8.0f);
			break;
		case Attribute::A_UV:
			EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
				elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_2, 0,
				sizeof(float) * 6.0f, sizeof(float) * 8.0f);

			break;
		default:
			return false;
			break;
		}
		return true;
	}

	void CubeCustom::render() const {
		//TODO
		EDK3::dev::GPUManager::Instance()->drawElements(
			EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 36, order_buffer.get(), EDK3::Type::T_UINT,
			0);
	}

} //EDK3
