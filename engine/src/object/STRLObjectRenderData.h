//
// Created by Sterling on 2/9/2024.
//

#ifndef STRLOBJECTRENDERDATA_H
#define STRLOBJECTRENDERDATA_H

#include <vector>
#include <memory>
#include "../util/observer/ISTRLObserver.h"
#include "STRLObject.h"

namespace strl
{

class IRenderer;
// Render Data for similar objects, to knock them out with one draw call
class STRLObjectRenderData : public ISTRLObserver<STRLObjectMessage>
{
public:
	explicit STRLObjectRenderData(IRenderer* renderer);
	~STRLObjectRenderData() override;

	[[nodiscard]] int get_render_group_index() const;
	void set_render_group_index(int render_group_index);

	[[nodiscard]] std::vector<float>& get_positions();
	void set_positions(const std::vector<float>& positions);
	[[nodiscard]] std::vector<float>& get_uvs();
	void set_uvs(const std::vector<float>& uvs);
	[[nodiscard]] std::vector<float>& get_colors();
	void set_colors(const std::vector<float>& colors);

	void add_renderer(IRenderer* renderer);

	void publish();

	void update(const STRLObjectMessage& message) override;

	void update_positions(STRLObject* object);
	void update_uvs(STRLObject* object);
	void update_colors(STRLObject* object);

private:
	// Set this to -1, will get updated when registered with the renderer
	int render_group_index_ = -1;
	// Render data, to be passed to the vertex shader
	std::vector<float> positions_;
	std::vector<float> uvs_;
	std::vector<float> colors_;

	IRenderer* renderer_ = nullptr;
};

} // strl

#endif //STRLOBJECTRENDERDATA_H
