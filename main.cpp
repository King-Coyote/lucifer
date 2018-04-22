#include <stdlib.h>
#include <cstdio>
#include <memory>
#include <omp.h>
#include <math.h>
#include <ctime>
#include "RenderScene.h"
#include "RenderObjectPlane.h"
#include "RenderObjectSphere.h"
#include "RenderMaterial.h"
#include "RenderObjectPointLight.h"
#include "Raytracer.h"
#include "RenderCamera.h"
#include "UniformRandomBit.h"
#include "ImageConverter.h"
#include "ObjectFactoryJson.h"

using namespace std;

int main(int argc, char** argv) {

	int width, height, samples;
	if (argc <= 2) {
		printf("Insufficent args specified, using default height=600/width=480/samples=10\n");
		width = 600;
		height = 480;
		samples = 10;
	} else {
		samples = atoi(argv[1]);
		width = atoi(argv[2]);
		height = atoi(argv[3]);
		if (height <= 0 || width <= 0) {
			printf("Invalid width/height specified, exiting\n");
			return 1;
		}
		if (samples == 0) {
			printf("Invalid samples specified, exiting\n");
			return 1;
		}
	}

    RenderScene mainScene = RenderScene();
	ObjectFactoryJson ofj("scene.json");
	mainScene.setObjects(ofj.createObjects());
	mainScene.setLights(ofj.createLights());
	// mainScene.setObjects(vector<unique_ptr<RenderObject>>());
	// mainScene.setLights(vector<unique_ptr<RenderObject>>());

	// POSITIONING:
	// z=0 is the floor, 1 is the ceiling.
	//TODO create a data-driven way of constructing a scene
    // mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0.5, 0), "Ceiling", Vec(0, 0, 1), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(0.9, 0.1, 0.2))));
	// mainScene.addObject(new RenderObjectPlane(Vec(0, 0.5, 0.5), "Left_Wall", Vec(1, 0, 0), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 0, 0))));
	// mainScene.addObject(new RenderObjectPlane(Vec(0.5, 1, 0.5), "Back_Wall", Vec(0, -1, 0), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 0, 0))));
	// mainScene.addObject(new RenderObjectPlane(Vec(1, 0.5, 0.5), "Right_Wall", Vec(-1, 0, 0), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(0.1, 1.0, 1.0))));
	// mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0.5, 1), "Floor", Vec(0, 0, -1), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 0, 0))));
	// mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0, 0.5), "Front_Wall", Vec(0, 1, 0), RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 0, 0))));

	// mainScene.addObject(new RenderObjectSphere(Vec(0.5, 1, 0.5), "diff_sphere", 0.2f, RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(0.0, 1.0, 1.0))));
	// mainScene.addObject(new RenderObjectSphere(Vec(0.7, 0.7, 0.4), "purp_sphere", 0.1f, RenderMaterial(RenderMaterialType::REFRACTIVE, Pixel(1.0f, 0, 0.9f))));

	// mainScene.addLight(new RenderObjectPointLight(Vec(0.8, 0.4, 0.9), "Main_Light", Pixel(1.0, 1.0, 1.0), 0.5));

	Pixel** pixels = new Pixel*[width];
	for (int i = 0; i<width; i++) {
		pixels[i] = new Pixel[height];
	}

	Raytracer raytracer = Raytracer();
	RenderCamera camera = RenderCamera(width, height, Vec(0.2, 0.01, 0.25), Vec(0.3, 1, 0.4));
	UniformRandomBit urb = UniformRandomBit();

	double timeBefore = omp_get_wtime();

	#pragma omp parallel private(urb) 
	{
		urb.setSeed((omp_get_thread_num() + 13)*47);
		#pragma omp for schedule(dynamic)
		for (int j = 0; j<height; j++) {
			fprintf(stdout, "Rendering percent complete: %.2f%%\r", ((double)j/height)*100);
			for (int i = 0; i<width; i++) {
				for (int s = 0; s<samples; s++) {
					Pixel radiance = Pixel();
					Ray mainRay = Ray(camera.getPosition(), camera.pixelToImage(i, j));
					raytracer.tracePixel(radiance, mainRay, mainScene, urb, 0);
					pixels[i][j] += radiance / samples;
				}
			}
		}
	}

	printf("Total time taken for render: %.3fs\n", omp_get_wtime() - timeBefore);

	ImageConverter ic = ImageConverter();
	ic.convertImage("render_image.png", width, height, pixels);

	for (int i = 0; i<width; i++) {
		delete pixels[i];
	}
	delete pixels;

}
