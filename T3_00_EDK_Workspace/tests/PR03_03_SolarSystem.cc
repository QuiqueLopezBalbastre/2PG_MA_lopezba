//
// PR03_00_Template.cc
// Ivan Sancho, Escuela Superior de Arte y Tecnologia
// Programacion Grafica
// ESAT 2022-2023
//

#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"
#include "ESAT/math.h"

#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"


//Unnamed struct and it's unique instance:
struct {
    EDK3::ref_ptr<EDK3::Camera> camera;
    EDK3::ref_ptr<EDK3::Node> root;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;
const int kmax_suns = 1;
const int kmax_planets = 4;
const int kmax_asteroids = 200;
const char** texture_paths;
float orbital_speed[204];

enum Celestial_body
{
    k_CB_Sun,
    k_CB_Planet,
    k_CB_Asteroid,
};

void CreateCube (Celestial_body type, float size, ESAT::Vec3 position)
{
    EDK3::ref_ptr<EDK3::Geometry> cube;
    EDK3::CreateCube(&cube, size, true, true);
    EDK3::ref_ptr<EDK3::Texture> texture;
    if (k_CB_Sun == type)
    {
        EDK3::Texture::Load("../../../assets/test/T_Sun.png", &texture);
    }
    if (k_CB_Planet == type)
    {
        EDK3::Texture::Load("../../../assets/test/T_Planeta_oceanico.png", &texture);
    }
    if (k_CB_Asteroid == type)
    {
        EDK3::Texture::Load("../../../assets/test/T_Asteroide.png", &texture);
    }
    if (!texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }
    EDK3::ref_ptr<EDK3::MatDiffuseTexture> mat_diff_text;
    mat_diff_text.alloc();
    EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> mat_diff_text_settings;
    mat_diff_text_settings.alloc();
    mat_diff_text_settings->set_texture(texture.get());

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(cube.get());
    drawable->set_material(mat_diff_text.get());
    drawable->set_material_settings(mat_diff_text_settings.get());
    drawable->set_position(position.x, position.y, position.z);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    GameState.root->addChild(drawable.get());
}

void InitScene() {
    //Allocating root node:
    EDK3::Node* root = GameState.root.alloc();

    //Allocating and initializing the camera:
    GameState.camera.alloc();
    float pos[] = { 120.0f, 120.0f, 120.0f };
    float view[] = { -120.0f, -120.0f, -120.0f };
    GameState.camera->set_position(pos);
    GameState.camera->set_view_direction(view);
    GameState.camera->setupPerspective(50.0f, (float)kWindowWidth / (float)kWindowHeight, 1.0f, 1500.0f);
    EDK3::dev::GPUManager::CheckGLError("Prepare END");

    CreateCube(k_CB_Sun, 20.0f, { 0.0f,0.0f,0.0f });
    //orbital_speed = (float*)malloc(kmax_planets + kmax_asteroids);
    for (int i = 0; i < kmax_planets; i++)
    {
        CreateCube(k_CB_Planet, ((float)(rand() % 601) / 100.0f + 2.0f), {40.0f + i * ((float)(rand()%10) + 10.0f), 0.0f, 0.0f });
        orbital_speed[i] = (float)(rand() % 1001) / 100.0f / 10000.0f;
    }
    for (int i = kmax_planets - 1; i < kmax_asteroids; i++)
    {
        CreateCube(k_CB_Asteroid, ((float)(rand() % 201) / 100.0f + 0.50f), { 0.0f, 0.0f, 0.0f });
        orbital_speed[i] = (float)(rand() % 301) / 100.0f / 10000.0f;
    }

 }

void UpdateFn() {
    EDK3::Node* sun = GameState.root->child(0);
    sun->set_rotation_y(ESAT::Time() / 100);
    for (int i = kmax_suns; i <= kmax_planets; i++)
    {
        EDK3::Node* planet = GameState.root->child(i);
        ESAT::Vec3 position = {(40.0f + i * 10.0f) * cos(ESAT::Time() * *(orbital_speed + i -1)), 0.0f, (40.0f + i * 10.0f) * sin(ESAT::Time() * *(orbital_speed + i -1))};
        planet->set_position(position.x, position.y, position.z);
    }
    for (int i = kmax_suns + kmax_planets; i <= kmax_asteroids; i++)
    {
        EDK3::Node* asteroid = GameState.root->child(i);
        ESAT::Vec3 position = { 100.0f * cos(ESAT::Time() * *(orbital_speed + i - 1)), 0.0f, 100.0f * sin(ESAT::Time() * *(orbital_speed + i - 1)) };
        if (i % 4 == 0)
        {
            position.y = 0.0f;
        }
        if (i % 4 == 1)
        {
            position.y = 5.0f;
        }
        if (i % 4 == 2)
        {
            position.y = -5.0f;
        }
        if (i % 4 == 3)
        {
            position.y = 10.0f;
        }
        asteroid->set_position(position.x, position.y, position.z);
    }
    GameState.camera->set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderFn() {
    //For every frame... determine what's visible:
    GameState.camera->doCull(GameState.root.get());

    //Rendering the scene:
    EDK3::dev::GPUManager::CheckGLError("begin Render-->");
    GameState.camera->doRender();
    EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
    ImGui::Begin("FPS Window");
    ImGui::Text("FPS: %0.1f", 1000.0 / dt);
    ImGui::Text("Delta time: %0.3f ms", dt);
    ImGui::End();
    ImGui::Render();
}

int ESAT::main(int argc, char** argv) {
    ESAT::WindowInit(kWindowWidth, kWindowHeight);
    srand(Time());
    InitScene();
    double dt = 0.0;
    double last_time = ESAT::Time();
    while (!ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape) &&
        ESAT::WindowIsOpened()) {
        UpdateFn();
        RenderFn();
        dt = ESAT::Time() - last_time;
        last_time = ESAT::Time();
        ImGuiFn(dt);
        ESAT::WindowFrame();
    }
    return 0;
}
