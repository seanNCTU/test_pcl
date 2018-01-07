#include <iostream>
#include <fstream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

int main(int argc, char** argv)
{
	pcl::PCDReader reader;
	pcl::PCDWriter writer;
	// Input pointcloud from file
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB> ());
	// Pointcloud that clone from input pointcloud if R value higher than threshold
	pcl::PointCloud<pcl::PointXYZRGB> clone;
	if(argc!=3)
	{
		std::cerr << "Not enough input, try again!" << std::endl;
		return 0;
	}
	// Threshold tuned by hand
	int r_thres = 120;

	reader.read (argv[1], *cloud);
	int length = cloud->points.size();
	std::cerr << cloud->points.size() << std::endl;
	int count = 0;
	for(int i = 0; i < length; ++i)
	{
		if(cloud->points[i].r > r_thres)
		{
			++count;
		}
	}
	std::cerr << "Valid number of points: " << count << std::endl;
	
	clone.width = count;
	clone.height = 1;
	clone.is_dense = true;
	clone.points.resize(clone.width * clone.height);
	int j = 0;
	for(int i = 0; i < length ; ++i)
	{
		if(cloud->points[i].r>r_thres)
		{
			clone.points[j].x = cloud->points[i].x;
			clone.points[j].y = cloud->points[i].y;
			clone.points[j].z = cloud->points[i].z;
			clone.points[j].r = cloud->points[i].r;
			clone.points[j].g = cloud->points[i].g;
			clone.points[j].b = cloud->points[i].b;
			++j;
		}
	}	
	writer.write<pcl::PointXYZRGB>(argv[2], clone, false);
	return 0;
}