#include "config.h"
#include "noise.h"
#include "world.h"

void create_world(int p, int q, world_func func, void *arg) {
    int pad = 1;
    for (int dx = -pad; dx < CHUNK_SIZE + pad; dx++) {
        for (int dz = -pad; dz < CHUNK_SIZE + pad; dz++) {
            int flag = 1;
            if (dx < 0 || dz < 0 || dx >= CHUNK_SIZE || dz >= CHUNK_SIZE) {
                flag = -1;
            }
            int x = p * CHUNK_SIZE + dx;
            int z = q * CHUNK_SIZE + dz;
            float f = simplex2(x * 0.01, z * 0.01, 4, 0.5, 2);
            float g = simplex2(-x * 0.01, -z * 0.01, 2, 0.9, 2);
            int mh = (g * 46) * WORLD_HEIGHT_SCALE;
            int h = f * mh + WORLD_HEIGHT;
            int w = 1;
            int v = 7;
            //int t = 15;
            if (h < WORLD_SEA_LEVEL) {
                w = 2;
                v = 2;
            }
            if (h >= WORLD_SNOW_LEVEL) {
                w = 9;
            }
            if (h > WORLD_HEIGHT_MAX) {
                h = WORLD_HEIGHT_MAX;
            }
            if (h < WORLD_HEIGHT_MIN) {
                h = WORLD_HEIGHT_MIN;
            }
            // Water
            for (int y = 0; y <= WORLD_SEA_LEVEL; y++) {
                func(x, y+2, z, 57 * flag, arg);
            }
            // sand and grass terrain
            for (int y = 1; y <= h; y++) {
                if (WORLD_ENABLE_BEDROCK) {
                    func(x, 0, z, 14 * flag, arg); // Bedrock
                }
                func(x, y, z, 6 * flag, arg); // Stone
                func(x, y+2, z, v * flag, arg); // Dirt
                func(x, y+3, z, w * flag, arg); // Grass
            }
            if (w == 1) {
                if (SHOW_PLANTS) {
                    // grass
                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
                        func(x, h+4, z, 17 * flag, arg);
                    }
                    // flowers
                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
                        func(x, h+4, z, w * flag, arg);
                    }
                }
                // trees
                int ok = SHOW_TREES;
                if (dx - 4 < 0 || dz - 4 < 0 ||
                    dx + 4 >= CHUNK_SIZE || dz + 4 >= CHUNK_SIZE)
                {
                    ok = 0;
                }
                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
                    for (int y = h + 4; y < h + 8; y++) {
                        for (int ox = -3; ox <= 3; ox++) {
                            for (int oz = -3; oz <= 3; oz++) {
                                int d = (ox * ox) + (oz * oz) +
                                    (y - (h + 4)) * (y - (h + 4));
                                if (d < 11) {
                                    func(x + ox, y+4, z + oz, 15, arg);
                                }
                            }
                        }
                    }
                    for (int y = h; y < h + 7; y++) {
                        func(x, y+4, z, 5, arg);
                    }
                }
            }
			// snow
			if (w == 9) {
				if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
					func(x, h+4, z, 28 * flag, arg);
				}
			}
            // clouds
            if (SHOW_CLOUDS) {
                for (int y = 64; y < 72; y++) {
                    if (simplex3(
                        x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
                    {
                        func(x, y, z, 16 * flag, arg);
                    }
                }
            }
        }
    }
}
