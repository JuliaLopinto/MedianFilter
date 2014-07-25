/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"
#include "MedianFilterCLP.h"
#include "stdlib.h"
#include "itkImageIOBase.h"

int main(int argc, char *argv[])
{  
  PARSE_ARGS ;

  // TEST FOR ARGC
  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile   outputImageFile  -r  valeurRadius" << std::endl;
    return EXIT_FAILURE;
    }


  // TEST FOR RADIUS VALUE
  if( radius < 1 )
  {
    std::cerr << "Radius has to be non nul and positive integer" << std::endl ;
    return EXIT_FAILURE ;
  }


  //Image Type//
  typedef itk::Image<unsigned char, 3> ImageType;
  
  //Input Image//
  typedef itk::ImageFileReader<ImageType> ReaderType; 
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(input);
  
  try
  {
    reader->Update();
  }
  catch(itk::ExceptionObject &err)
  {
    return EXIT_FAILURE;
  }


  //Median Filtering//
  typedef itk::MedianImageFilter<ImageType, ImageType >  FilterType;

  FilterType::Pointer filter = FilterType::New();
  FilterType::InputSizeType filterRadius;
  filterRadius.Fill(radius);
  filter->SetRadius(filterRadius);
  filter->SetInput(reader->GetOutput());


  //Output Image
  typedef itk::ImageFileWriter<ImageType> WriterType;  
  WriterType::Pointer writer = WriterType::New(); 
  writer->SetInput(filter->GetOutput()); 
  writer->SetFileName(output);


  try
  {
    writer->Update();
  }
  catch(itk::ExceptionObject &err)
  {
    return EXIT_FAILURE;
  } 
  return EXIT_SUCCESS ;
 
}
