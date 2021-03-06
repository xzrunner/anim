#pragma once

#include <anim/typedef.h>

#include <node0/typedef.h>
#include <painting0/Color.h>
#include <painting2/SRT.h>

#include <boost/noncopyable.hpp>

#include <vector>

namespace anim
{

class AnimInstance;

class AnimTemplate : boost::noncopyable
{
public:
	AnimTemplate();

	void Clear();

	void Build(const std::vector<LayerPtr>& layers);

	int GetMaxFrameIdx() const { return m_max_frame_idx; }
	int GetMaxItemNum() const { return m_max_item_num; }

	const std::vector<n0::SceneNodePtr>& GetAllSlots() const {
		return m_slots;
	}

	void AddInstance(const std::shared_ptr<AnimInstance>& instance);
	bool OnlyOneInstance() const { return m_instances.size() == 1; }

private:
	void SetCountNum(const std::vector<LayerPtr>& layers);
	void FillingLayers(const std::vector<LayerPtr>& layers);
	void ConnectItems(const std::vector<LayerPtr>& layers);
	void LoadLerpData(const std::vector<LayerPtr>& layers);
	void CreateSprSlots(const std::vector<LayerPtr>& layers);

	void RefreshInstances();

	static void CalcDeltaColor(const pt0::Color& begin,
		const pt0::Color& end, int time, float* ret);

private:
	struct Lerp
	{
		pt2::SRT srt, dsrt;

		pt0::Color col_mul, col_add;
		float dcol_mul[4], dcol_add[4];
	};

	struct Item
	{
		int16_t next, prev;
		int16_t slot;
		int16_t lerp;

		n0::SceneNodePtr node = nullptr;

		Item();
	};

	struct Frame
	{
		int frame_idx;
		std::vector<Item> items;

//		std::vector<std::pair<AnimLerp::SprData, std::unique_ptr<ILerp>>> lerps;
	};

	struct Layer
	{
		std::vector<Frame> frames;
	};

private:
	std::vector<Layer> m_layers;

	std::vector<n0::SceneNodePtr> m_slots;

	std::vector<Lerp> m_lerps;

	int m_max_frame_idx;
	int m_max_item_num;

	std::vector<std::weak_ptr<AnimInstance>> m_instances;

	friend class AnimInstance;

}; // AnimTemplate

}