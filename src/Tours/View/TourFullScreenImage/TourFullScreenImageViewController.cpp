// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageViewController.h"
#include "ITourFullScreenImageViewModel.h"
#include "ITourFullScreenImageView.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageViewController::TourFullScreenImageViewController(ITourFullScreenImageViewModel& viewModel,
                                                                                     ITourFullScreenImageView& view)
                : m_viewModel(viewModel)
                , m_view(view)
                , m_beginFullScreenImageCeremonyCallback(this, &TourFullScreenImageViewController::OnCeremonyBegin)
                , m_endFullScreenImageCeremonyCallback(this, &TourFullScreenImageViewController::OnCeremonyEnd)
                {
                    m_viewModel.InsertBeginCeremonyCallback(m_beginFullScreenImageCeremonyCallback);
                    m_viewModel.InsertEndCeremonyCallback(m_endFullScreenImageCeremonyCallback);
                }
                
                TourFullScreenImageViewController::~TourFullScreenImageViewController()
                {
                    m_viewModel.RemoveBeginCeremonyCallback(m_beginFullScreenImageCeremonyCallback);
                    m_viewModel.RemoveEndCeremonyCallback(m_endFullScreenImageCeremonyCallback);
                }
                
                void TourFullScreenImageViewController::OnCeremonyBegin()
                {
                    m_view.BeginCeremony(m_viewModel.GetAsset(),
                                         m_viewModel.GetMessage());
                }
                
                void TourFullScreenImageViewController::OnCeremonyEnd()
                {
                    m_view.EndCeremony();
                }
            }
        }
    }
}
