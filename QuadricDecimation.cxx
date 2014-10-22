#include <vtkPolyData.h>
#include <vtkQuadricDecimation.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkSTLReader> reader =
		vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();
	vtkPolyData *inputPolyData = reader->GetOutput();

	std::cout << "Before decimation" << std::endl << "------------" << std::endl;
	std::cout << "There are " << inputPolyData->GetNumberOfPoints() << " points." << std::endl;
	std::cout << "There are " << inputPolyData->GetNumberOfPolys() << " polygons." << std::endl;

	vtkSmartPointer<vtkQuadricDecimation> decimate =
		vtkSmartPointer<vtkQuadricDecimation>::New();
	decimate->SetInputConnection(inputPolyData->GetProducerPort());
	decimate->SetTargetReduction(0.8);
	decimate->Update();

	vtkPolyData *decimated = decimate->GetOutput();

	std::cout << "After decimation" << std::endl << "------------" << std::endl;

	std::cout << "There are "
		<< decimated->GetNumberOfPoints() << " points." << std::endl;
	std::cout << "There are "
		<< decimated->GetNumberOfPolys() << " polygons." << std::endl;

	vtkSmartPointer<vtkSTLWriter> writer =
		vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(argv[2]);
	writer->SetInput(decimated);
	writer->SetFileTypeToBinary();
	writer->Write();

	return EXIT_SUCCESS;
}
