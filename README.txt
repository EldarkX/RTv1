usage:
	./rtv1 [file_name].scene

[file_name].scene:
	camera:
	{
		location: [-1000 - 1000] [-1000 - 1000] [-1000 - 1000]
		rotation: [-360 - 360] [-360 - 360] [-360 - 360]		
	}
	[plane]:
	{
		location: [-1000 - 1000] [-1000 - 1000] [-1000 - 1000]
		rotation: [-360 - 360] [-360 - 360] [-360 - 360]
	}	
	[sphere | cylinder]:
	{
		location: [-1000 - 1000] [-1000 - 1000] [-1000 - 1000]
		rotation: [-360 - 360] [-360 - 360] [-360 - 360]
		color: [0 - 255] [0 - 255] [0 - 255]
		radius [0.xx - 1000.xx]
	}
	[cone]:
	{
		location: [-1000 - 1000] [-1000 - 1000] [-1000 - 1000]
		rotation: [-360 - 360] [-360 - 360] [-360 - 360]
		color: [0 - 255] [0 - 255] [0 - 255]
		angle [-150.xx - 150.xx]
	}
	[light]:
	{
		location: [-1000 - 1000] [-1000 - 1000] [-1000 - 1000]
		rotation: [-360 - 360] [-360 - 360] [-360 - 360]
		radius: [0.xx - 1]	
		type: AMBIENT | DIFFUSE
	}