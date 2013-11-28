% openCV embedded notice d'utilisation
% TEXIER Pierre-jean
% Année 2013/2014

Synopsis
========

Petit tutoriel permettant d'implémenter openCV sur plateforme ARM (Olinuxino A20)

Description
===========



Using `openCV` version 2.4.7
--------------

Préambule : L'environnement 
=====


Téléchargement via git --> commande : 
------------------------
	git clone https://github.com/Itseez/opencv.git
	
	
	
Configuration
=====

	cd openCV.2.4.7/platforms/linux
	mkdir release && cd release
	su -c 'aptitude install cmake-gui'
	cmake-gui
	
	Choisir: 
	unix Makefiles
	Specify options for cross-compiling
	Operating system : Linux
	Processor : arm
	Puis rentrer le chemin de la chaine de compilation-croisée
	
	Cocher : 
	
	BUILD_JPEG
	BUILD_SHARED_LIBS
	BUILD_WITH_DEBUG_INFO
	BUILD_opencv_apps
	BUILD_opencv_calib3d
	BUILD_opencv_contrib
	BUILD_opencv_core
	BUILD_opencv_features2d
	BUILD_opencv_flann
	BUILD_opencv_gpu
	BUILD_opencv_highgui
	BUILD_opencv_imgproc
	BUILD_opencv_legacy
	BUILD_opencv_ml
	BUILD_opencv_nonfree
	BUILD_opencv_objdetect
	BUILD_opencv_ocl
	BUILD_opencv_photo
	BUILD_opencv_stitching
	BUILD_opencv_video
	BUILD_opencv_videostab
	WITH_GSTREAMER
	WITH_JPEG
	WITH_V4L

Compilation
=====
	make -j2
	su -c 'make install'
	
Copie des librairies sur la plateforme dans /usr/lib
=====	
	
	scp libopencv_ml.so.2.4 \
	libopencv_calib3d.so.2.4 \
	libopencv_stitching.so.2.4 \
	libopencv_gpu.so.2.4 \
	libopencv_nonfree.so.2.4 \
	libopencv_contrib.so.2.4 \
	libopencv_video.so.2.4 \
	libopencv_highgui.so.2.4 \
	libopencv_objdetect.so.2.4 \
	libopencv_core.so.2.4 \
	libopencv_videostab.so.2.4 \
	libopencv_imgproc.so.2.4 \
	libopencv_ocl.so.2.4 \
	libopencv_features2d.so.2.4 \
	libopencv_legacy.so.2.4 \
	libopencv_photo.so.2.4 \
	libopencv_flann.so.2.4 \
	root@adresse_ip:/usr/lib	






