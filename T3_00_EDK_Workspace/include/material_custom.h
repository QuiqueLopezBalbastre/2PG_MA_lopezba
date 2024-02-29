/**
 *
 * @brief Custom material header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __MATERIAL_CUSTOM_H__
#define __MATERIAL_CUSTOM_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/texture.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"


namespace EDK3 {

class MaterialCustom : public EDK3::Material {
 public:
  MaterialCustom();
  void init(const char* vertex_shader_path, const char* fragment_shader_path);

  virtual bool enable(const EDK3::MaterialSettings *mat) const override;
  virtual void setupCamera(const float projection[16], const float view[16]) const override;
  virtual void setupModel(const float model[16]) const override;

  virtual unsigned int num_attributes_required() const;
  virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
  virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;


  class MaterialCustomSettings : public EDK3::MaterialSettings {
   public:
    MaterialCustomSettings() {
      memset(color_, 0, sizeof(color_));
    }
    void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
    const float* color() const { return color_; }
   protected:
    virtual ~MaterialCustomSettings() {}
   private:
    MaterialCustomSettings(const MaterialCustomSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
    }
    MaterialCustomSettings(MaterialCustomSettings&& other) {
      memcpy(color_, other.color_, sizeof(color_));
      memset(other.color_, 0, sizeof(color_));
    }
    MaterialCustomSettings& operator=(const MaterialCustomSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      return *this;
    }
    float color_[4];
  }; //MaterialCustomSettings
  class MaterialCustomTextureSettings : public EDK3::MaterialSettings {
  public:
    MaterialCustomTextureSettings() {
      memset(color_, 0, sizeof(color_));
    }
    void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
    const float* color() const { return color_; }
    void set_texture(EDK3::ref_ptr<EDK3::Texture> t, const int i) { texture_[i] = t; }
    EDK3::ref_ptr<EDK3::Texture>texture(const int i) const { return texture_[i]; };
  protected:
    virtual ~MaterialCustomTextureSettings() {}
  private:
    MaterialCustomTextureSettings(const MaterialCustomTextureSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      texture_[0] = other.texture_[0];
      texture_[1] = other.texture_[1];
    }
    MaterialCustomTextureSettings(MaterialCustomTextureSettings&& other) {
      memcpy(color_, other.color_, sizeof(color_));
      memset(other.color_, 0, sizeof(color_));
      texture_[0] = other.texture_[0];
      texture_[1] = other.texture_[1];
      other.texture_[0].release();
      other.texture_[1].release();
    }
    MaterialCustomTextureSettings& operator=(const MaterialCustomTextureSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      return *this;
    }
    float color_[4];
    EDK3::ref_ptr<EDK3::Texture> texture_[2];
  }; //MaterialCustomTextureSettings


 protected:
  virtual ~MaterialCustom();

 private:
  EDK3::ref_ptr<EDK3::dev::Program> program_;

  MaterialCustom(const MaterialCustom&);
  //MaterialCustom(MaterialCustom&&);
  MaterialCustom& operator=(const MaterialCustom&);
};

} //EDK3

#endif //__MATERIAL_CUSTOM_H__
