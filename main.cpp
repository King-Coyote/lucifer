#include <stdlib.h>
#include <cstdio>
#include <memory>
#include <Magick++.h>
#include "RenderScene.h"
#include "RenderObjectPlane.h"
#include "RenderMaterial.h"
#include "RenderObjectPointLight.h"
#include "Raytracer.h"
#include "RenderCamera.h"
#include "UniformRandomBit.h"

int main(int argc, char** argv) {

	int width, height;
	if (argc <= 2) {
		printf("Insufficent args specified, using default height/width/samples");
		width = 600;
		height = 480;
	} else {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
		if (height <= 0 || width <= 0) {
			printf("Invalid width/height specified, exiting");
			return 1;
		}
	}

    RenderScene mainScene = RenderScene();
    mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0.5, 0), Vec(0, 0, 1), "Floor", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));
	mainScene.addObject(new RenderObjectPlane(Vec(0, 0.5, 0.5), Vec(1, 0, 0), "Left_Wall", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));
	mainScene.addObject(new RenderObjectPlane(Vec(0.5, 1, 0.5), Vec(0, -1, 0), "Back_Wall", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));
	mainScene.addObject(new RenderObjectPlane(Vec(1, 0.5, 0.5), Vec(-1, 0, 0), "Right_Wall", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));
	mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0.5, 1), Vec(0, 0, -1), "Ceiling", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));
	mainScene.addObject(new RenderObjectPlane(Vec(0.5, 0, 0.5), Vec(0, 1, 0), "Front_Wall", RenderMaterial(RenderMaterialType::DIFFUSE, Pixel(1.0, 1.0, 1.0))));

	mainScene.addLight(new RenderObjectPointLight(Vec(0.5, 0.5, 0.5), "Main_Light", Pixel(0.5, 1.0, 1.0), 10.0));

	Pixel** pixels = new Pixel*[width];
	for (int i = 0; i<width; i++) {
		pixels[i] = new Pixel[height];
	}

	Raytracer raytracer = Raytracer();
	RenderCamera camera = RenderCamera(width, height, Vec(0.5, 0.05, 0.9), Vec(0, 0.5, -0.3));
	UniformRandomBit urb = UniformRandomBit();
	int samples = 1;
	urb.setSeed(543); //TODO magic numbers for samples and seed; defaultist trash. Replace with hardware random/ args

	// TODO: multithread this part u fukcin kunt (main loop)
	for (int j = 0; j<height; j++) {
		for (int i = 0; i<width; i++) {
			for (int s = 0; s<samples; s++) {
				Pixel radiance = Pixel();
				Ray mainRay = Ray(camera.getPosition(), camera.pixelToImage(i, j));
				raytracer.tracePixel(radiance, mainRay, mainScene, urb, 0);
				pixels[i][j] += radiance / samples;
			}
		}
	}

	//TODO make the image save correctly
	Magick::Image image = Magick::Image(Magick::Geometry(width, height), Magick::Color("magenta"));

	for (int i = 0; i<width; i++) {
		delete pixels[i];
	}
	delete pixels;

}
