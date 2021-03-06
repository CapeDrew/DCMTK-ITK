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
#ifndef __itkBinaryThresholdImageFunction_hxx
#define __itkBinaryThresholdImageFunction_hxx

#include "itkBinaryThresholdImageFunction.h"

namespace itk
{
template< class TInputImage, class TCoordRep >
BinaryThresholdImageFunction< TInputImage, TCoordRep >
::BinaryThresholdImageFunction()
{
  m_Lower = NumericTraits< PixelType >::NonpositiveMin();
  m_Upper = NumericTraits< PixelType >::max();
}

/**
 * Values greater than or equal to the value are inside
 */
template< class TInputImage, class TCoordRep >
void
BinaryThresholdImageFunction< TInputImage, TCoordRep >
::ThresholdAbove(PixelType thresh)
{
  if ( m_Lower != thresh
       || m_Upper != NumericTraits< PixelType >::max() )
    {
    m_Lower = thresh;
    m_Upper = NumericTraits< PixelType >::max();
    this->Modified();
    }
}

/**
 * The values less than or equal to the value are inside
 */
template< class TInputImage, class TCoordRep >
void
BinaryThresholdImageFunction< TInputImage, TCoordRep >
::ThresholdBelow(PixelType thresh)
{
  if ( m_Lower != NumericTraits< PixelType >::NonpositiveMin()
       || m_Upper != thresh )
    {
    m_Lower = NumericTraits< PixelType >::NonpositiveMin();
    m_Upper = thresh;
    this->Modified();
    }
}

/**
 * The values less than or equal to the value are inside
 */
template< class TInputImage, class TCoordRep >
void
BinaryThresholdImageFunction< TInputImage, TCoordRep >
::ThresholdBetween(PixelType lower, PixelType upper)
{
  if ( m_Lower != lower
       || m_Upper != upper )
    {
    m_Lower = lower;
    m_Upper = upper;
    this->Modified();
    }
}

template< class TInputImage, class TCoordRep >
void
BinaryThresholdImageFunction< TInputImage, TCoordRep >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Lower: " << m_Lower << std::endl;
  os << indent << "Upper: " << m_Upper << std::endl;
}
} // end namespace itk

#endif
