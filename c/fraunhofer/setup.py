def configuration(parent_package = '', top_path = None):

    from numpy.distutils.misc_util import Configuration

    config = Configuration(
        package_name = None,
        parent_name = parent_package,
        top_path = top_path
    )

    config.add_extension(
        'fraunhofer',
        ['fraunhofer_ufunc.c'],
        libraries = ["tmpl"]
    )

    return config

if __name__ == "__main__":
    from numpy.distutils.core import setup
    setup(configuration = configuration)
