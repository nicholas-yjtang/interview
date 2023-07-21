#!/bin/bash
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
pushd $CURRENT_DIR/..
RELEASE_NAME="jupyterhub"
VERSION="3.0.0-beta.3"
K8S_NAMESPACE="jupyterhub"
helm upgrade --cleanup-on-fail \
  --install $RELEASE_NAME jupyterhub/jupyterhub \
  --namespace $K8S_NAMESPACE \
  --create-namespace \
  --version=$VERSION \
  --values config/config.yaml
popd
