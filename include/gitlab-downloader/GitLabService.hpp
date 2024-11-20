#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <drogon/drogon.h>
#include <fmt/format.h>
#include "models/Pipeline.hpp"

namespace gitlab
{

    class GitLabService
    {
    public:
        GitLabService(const std::string &baseUrl, const std::string &token);

        void getRecentPipelines(
            const std::string &projectId,
            std::function<void(PipelineResponse)> &&callback);

        void downloadArtifact(
            const std::string &projectId,
            const std::string &pipelineId,
            const std::string &artifactPath,
            std::function<void(std::string)> &&callback);

    private:
        std::string baseUrl_;
        std::string token_;
        std::shared_ptr<drogon::HttpClient> httpClient_;

        void setupRequest(drogon::HttpRequestPtr &req);
        std::string buildUrl(const std::string &endpoint);
    };

} // namespace gitlab