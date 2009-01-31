/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageFileWriterStreamingTest2.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifdef __BORLANDC__
#define ITK_LEAN_AND_MEAN
#endif

#include <fstream>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkPipelineMonitorImageFilter.h"
#include "itkDifferenceImageFilter.h"


typedef unsigned char            PixelType;
typedef itk::Image<PixelType,3>  ImageType;

typedef itk::ImageFileReader<ImageType>         ReaderType;
typedef itk::ImageFileWriter< ImageType >       WriterType;


bool SameImage(std::string output, std::string baseline) {
  
  double intensityTolerance = 0.0;
  unsigned int radiusTolerance = 0.0;
  unsigned int numberOfPixelTolerance = 0;
  
  ReaderType::Pointer testReader = ReaderType::New();
  ReaderType::Pointer baselineReader = ReaderType::New();
  testReader->SetFileName(output);
  baselineReader->SetFileName(baseline);
  
  typedef itk::DifferenceImageFilter<ImageType,ImageType> DiffType;
  DiffType::Pointer diff = DiffType::New();
  diff->SetValidInput(baselineReader->GetOutput());
  diff->SetTestInput(testReader->GetOutput());
  diff->SetDifferenceThreshold( intensityTolerance );
  diff->SetToleranceRadius( radiusTolerance );
  diff->UpdateLargestPossibleRegion();

   unsigned long status = 0;
   status = diff->GetNumberOfPixelsWithDifferences();

   if (status > numberOfPixelTolerance)
     return false;
   return true;
}

// This test is designed to improve coverage and test boundary cases 
int itkImageFileWriterStreamingTest2(int argc, char* argv[])
{


  if( argc < 3 )
    { 
    std::cerr << "Usage: " << argv[0] << " input output " << std::endl;
    return EXIT_FAILURE;
    }
      
  // We remove the output file
  itksys::SystemTools::RemoveFile(argv[2]); 

  //

  
  unsigned int numberOfDataPieces = 4;
  
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->SetUseStreaming( true );
    
  typedef itk::PipelineMonitorImageFilter<ImageType> MonitorFilter;
  MonitorFilter::Pointer monitor = MonitorFilter::New();
  monitor->SetInput(reader->GetOutput());
  
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(argv[2]);
  writer->SetInput(monitor->GetOutput());
  writer->SetNumberOfStreamDivisions(numberOfDataPieces);

  if (std::string(argv[2]) != writer->GetFileName()) 
    return EXIT_FAILURE;

  if (numberOfDataPieces != writer->GetNumberOfStreamDivisions()) 
    return EXIT_FAILURE;

  // write the whole image
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
  if (monitor->GetNumberOfUpdates() != 4) 
    {
    std::cout << monitor;
    return EXIT_FAILURE;
    }

  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;

  

  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  // get the size of the image
  reader->GenerateOutputInformation();
  ImageType::RegionType largestRegion;
  largestRegion = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
  itk::ImageIORegion  ioregion(3);


  ////////////////////////////////////////////////
  // test 1x1 size
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]+largestRegion.GetSize()[0]/2 );
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]+largestRegion.GetSize()[1]/2 );
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]+largestRegion.GetSize()[2]/2 );
  ioregion.SetSize(0, 1);
  ioregion.SetSize(1, 1);
  ioregion.SetSize(2, 1);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
  if (monitor->GetNumberOfUpdates() != 1) 
    {
    std::cout << monitor;
    return EXIT_FAILURE;
    }

  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;

  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  ////////////////////////////////////////////////
  // test 2x2 with odd offset
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]+largestRegion.GetSize()[0]/2 + 1);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]+largestRegion.GetSize()[1]/2 + 1);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]+largestRegion.GetSize()[2]/2 + 1);
  ioregion.SetSize(0, 2);
  ioregion.SetSize(1, 2);
  ioregion.SetSize(2, 2);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;


  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  ////////////////////////////////////////////////
  // test long skiny 
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]);
  ioregion.SetSize(0, 1);
  ioregion.SetSize(1, 1);
  ioregion.SetSize(2, largestRegion.GetSize()[2]);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;


  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  ////////////////////////////////////////////////
  // test long skiny 
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]);
  ioregion.SetSize(0, 1);
  ioregion.SetSize(1, largestRegion.GetSize()[1]);
  ioregion.SetSize(2, 1);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }

  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;

  


  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  ////////////////////////////////////////////////
  // test full region
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]);
  ioregion.SetSize(0, largestRegion.GetSize()[0]);
  ioregion.SetSize(1, largestRegion.GetSize()[1]);
  ioregion.SetSize(2, largestRegion.GetSize()[2]);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
  if (monitor->GetNumberOfUpdates() != 4) 
    {
    std::cout << monitor;
    return EXIT_FAILURE;
    }

  if (!SameImage( argv[1], argv[2])) 
    return EXIT_FAILURE;



  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  bool thrownException = false;
  ////////////////////////////////////////////////
  // test out of bounds region
  ioregion.SetIndex(0, largestRegion.GetIndex()[0] - 1);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]);
  ioregion.SetSize(0, largestRegion.GetSize()[0]);
  ioregion.SetSize(1, largestRegion.GetSize()[1]);
  ioregion.SetSize(2, largestRegion.GetSize()[2]);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {    
    thrownException = true;
    }
  
  if (!thrownException)
    return EXIT_FAILURE;


  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  thrownException = false;
  ////////////////////////////////////////////////
  // test out of bounds region
  ioregion.SetIndex(0, largestRegion.GetIndex()[0]+largestRegion.GetSize()[0]/2 + 1);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]+largestRegion.GetSize()[1]/2 + 1);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]+largestRegion.GetSize()[2]/2 + 1);
  ioregion.SetSize(0, largestRegion.GetSize()[0]);
  ioregion.SetSize(1, largestRegion.GetSize()[1]);
  ioregion.SetSize(2, largestRegion.GetSize()[2]+1);

  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {    
    thrownException = true;
    }
  
  if (!thrownException)
    return EXIT_FAILURE;


  
  reader->Modified();
  monitor->ClearPipelineSavedInformation();
  thrownException = false;
  ////////////////////////////////////////////////
  // test when regions aren't matching
  ImageType::RegionType halfLargestRegion;
  halfLargestRegion.SetIndex(largestRegion.GetIndex());
  halfLargestRegion.SetSize(0, largestRegion.GetSize()[0]/2);
  halfLargestRegion.SetSize(1, largestRegion.GetSize()[1]/2);
  halfLargestRegion.SetSize(2, largestRegion.GetSize()[2]/2);


  monitor->GetOutput()->SetRequestedRegion(halfLargestRegion);
  monitor->GetOutput()->Update();

  ioregion.SetIndex(0, largestRegion.GetIndex()[0]);
  ioregion.SetIndex(1, largestRegion.GetIndex()[1]);
  ioregion.SetIndex(2, largestRegion.GetIndex()[2]);
  ioregion.SetSize(0, largestRegion.GetSize()[0]/3);
  ioregion.SetSize(1, largestRegion.GetSize()[1]/3);
  ioregion.SetSize(2, largestRegion.GetSize()[2]/3);


  writer->SetIORegion(ioregion);
  
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {        
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }
  
   if (monitor->GetNumberOfUpdates() != 1) 
    {
    std::cout << monitor;
    return EXIT_FAILURE;
    }

   if (!SameImage( argv[1], argv[2])) 
     return EXIT_FAILURE;


  return EXIT_SUCCESS;
}