from setuptools import setup, find_packages

setup(
    name="litenet",
    version="0.1.0",
    package_dir={"": "src/python"},
    packages=find_packages(where="src/python"),
    package_data={
        'litenet': ['_litenet_core.dylib', '_litenet_core.so']
    },
    include_package_data=True,
    description="A lightweight machine learning library",
    install_requires=[
        "numpy>=1.20.0",
    ],
    python_requires=">=3.11",
)