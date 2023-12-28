# Use an official Ubuntu as a parent image
FROM python:3.8-slim

ARG VERSION
ARG BOARD
ENV BOARD=${BOARD}

# Navigate to the CircuitPython directory
WORKDIR /circuitpython

# Install system dependencies for CircuitPython build
RUN apt-get update && apt-get install -y \
    git \
    make \
    cmake \
    ninja-build \
    libusb-1.0-0 \
    && rm -rf /var/lib/apt/lists/*

# Install Git Large File Storage (git-lfs)
RUN apt-get update && \
    apt-get install -y git-lfs && \
    git lfs install && \
    rm -rf /var/lib/apt/lists/*

# Clone the CircuitPython repository
RUN git clone https://github.com/adafruit/circuitpython.git . && \
    git checkout $VERSION

# Copy the files for the external C modules configuration
COPY py/*.mk py/

RUN cd ports/espressif && make fetch-port-submodules

# Install Python dependencies from requirements-dev.txt
RUN pip install -r requirements-dev.txt
# As part of the build process, mpy-cross is needed to compile .py files into .mpy files. To compile (or recompile) mpy-cross:
RUN make -C mpy-cross

WORKDIR /circuitpython/ports/espressif
RUN esp-idf/install.sh
RUN /root/.espressif/python_env/idf4.4_py3.8_env/bin/python -m pip install --no-cache-dir minify_html jsmin

VOLUME ["/root/build"]

# Set the default command for the container
CMD ["/bin/bash", "-c", "source esp-idf/export.sh && make -j$(nproc) BOARD=$BOARD && cp -r build-$BOARD/* /root/build"]