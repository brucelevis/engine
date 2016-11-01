#pragma once

#include "voxel/polyvox/RawVolume.h"
#include "io/File.h"
#include "core/Color.h"

namespace voxel {

class VoxFileFormat {
protected:
	std::vector<glm::vec4> _palette;
	size_t _paletteSize = 0;

	VoxelType findVoxelType(const glm::vec4& color) const;
	glm::vec4 findClosestMatch(const glm::vec4& color) const;
	glm::vec4 paletteColor(uint32_t index) const;
public:
	virtual ~VoxFileFormat() {
	}

	virtual RawVolume* load(const io::FilePtr& file) = 0;
	virtual bool save(const RawVolume* volume, const io::FilePtr& file) = 0;
};

}
