//
// Created by Sterling on 2/9/2024.
//

#ifndef OPENGLRENDERDATA_H
#define OPENGLRENDERDATA_H

#include <vector>
#include <memory>
#include <format>
#include "../../util/observer/ISTRLObserver.h"
#include "../../core/object/STRLObject.h"
#include "../../core/event/STRLEvent.h"
#include "OpenGLTexture.h"
#include "OpenGLShader.h"
#include "../STRLCamera.h"

namespace strl
{

const int STRL_POSITION_VERTEX_SIZE = 3;
const int STRL_UV_VERTEX_SIZE = 2;
const int STRL_COLOR_VERTEX_SIZE = 4;

// Render Data for similar objects, to knock them out with one draw call
class OpenGLRenderData : public STRLManagedItemBase
{
public:
	OpenGLRenderData(std::string name,
		std::vector<std::string> tags,
		OpenGLShader* shader,
		STRLCamera* camera,
		std::function<void()> shader_update_function = nullptr);
	~OpenGLRenderData();

	void shader_update();
	void set_shader_update_function(std::function<void()> function);

	[[nodiscard]] std::vector<float>& get_positions();
	void set_positions(const std::vector<float>& positions);
	[[nodiscard]] std::vector<float>& get_uvs();
	void set_uvs(const std::vector<float>& uvs);
	[[nodiscard]] std::vector<float>& get_colors();
	void set_colors(const std::vector<float>& colors);
	std::vector<int>& get_indices();

	void set_indices(const std::vector<int>& indices);
	void update_positions(STRLObject* object);
	void update_uvs(STRLObject* object);
	void update_colors(STRLObject* object);

	void update_indices(STRLObject* object);
	void add_points(STRLObject* updated_object, int points_added, std::vector<STRLObject*>& objects);

	void remove(STRLObject* remove_object, std::vector<STRLObject*>& objects);

	void update_locations(std::vector<STRLObject*>& objects);
	[[nodiscard]] bool has_positions_updated() const;
	void set_positions_updated(bool positions_updated);
	[[nodiscard]] bool has_uvs_updated() const;
	void set_uvs_updated(bool uvs_updated);
	[[nodiscard]] bool has_colors_updated() const;
	void set_colors_updated(bool colors_updated);
	[[nodiscard]] bool has_indices_updated() const;

	void set_indices_updated(bool indices_updated);
	[[nodiscard]] unsigned int& get_vao();
	void set_vao(unsigned int vao);
	unsigned int& get_vbo(int index);
	std::vector<unsigned int>& get_all_vbos();
	void set_vbo(int index, unsigned int vbo);
	void set_vbos(std::vector<unsigned int> vbos);
	[[nodiscard]] unsigned int& get_ebo();
	void set_ebo(unsigned int ebo);
	int get_last_update_size(int index);

	void set_last_update_size(int index, int size);
	std::unique_ptr<OpenGLTexture>& get_texture();
	void set_texture(std::unique_ptr<OpenGLTexture>& texture);

	void create_texture(const std::string& path = "");
	[[nodiscard]] int get_last_object_index() const;

	void set_last_object_index(int object_index);

	[[nodiscard]] STRLRenderMode get_mode() const;
	void set_mode(STRLRenderMode mode);

private:
	OpenGLShader* shader_;
	STRLCamera* camera_;
	// Render data, to be passed to the vertex shader
	std::vector<float> positions_;
	std::vector<float> uvs_;
	std::vector<float> colors_;
	std::vector<int> indices_;

	bool positions_updated_ = true;
	bool uvs_updated_ = true;
	bool colors_updated_ = true;
	bool indices_updated_ = true;

	unsigned int vao_{};
	std::vector<unsigned int> vbos_;
	unsigned int ebo_{};
	std::vector<int> last_updated_size_;

	std::unique_ptr<OpenGLTexture> texture_;

	int last_object_index_{};

	std::vector<std::pair<int, int>> updated_position_index_and_count_;
	std::vector<std::pair<int, int>> updated_indices_index_and_count_;

	// User defined function for updating shader
	std::function<void()> shader_update_function_;

	STRLRenderMode mode_;

	std::pair<int, int> get_min_max_indices(STRLObject* object);
	std::vector<int> get_object_indices(STRLObject* object);
	std::vector<float> get_float_points(STRLObject* object);

};

} // strl

#endif //OPENGLRENDERDATA_H
