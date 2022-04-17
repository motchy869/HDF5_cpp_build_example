#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <type_traits>

//#define H5_BUILT_AS_DYNAMIC_LIB 1 // In Windows, turn on this when using hdf5 as a shared library.
#include <H5Cpp.h>

template<typename T>
T sinc(const T x);

template<typename T>
T mathFunc_f(const T x1, const T x2);

int main() {
    constexpr float x1_start = -10.0, x2_start = -10.0;
    constexpr float x1_end = 10.0, x2_end = 10.0;
    constexpr float x1_step = 0.5, x2_step = 0.5;
    constexpr int N1 = static_cast<int>((x1_end - x1_start)/x1_step + 0.5f) + 1;
    constexpr int N2 = static_cast<int>((x2_end - x2_start)/x2_step + 0.5f) + 1;

    const std::string fileName("test.h5");

    H5::H5File file(fileName, H5F_ACC_TRUNC);

    H5::FloatType datatype(H5::PredType::NATIVE_FLOAT);
    datatype.setOrder(H5T_ORDER_LE);

    H5::Group group_gridData(file.createGroup("gridData"));
    H5::Group group_metaData(group_gridData.createGroup("metaData"));


    /* Set points. */
    {
        hsize_t dims[] = {N1, N2};
        H5::DataSpace dataSpace(2, dims);
        H5::DataSet dataSet(group_gridData.createDataSet("points", datatype, dataSpace));

        float dataSet_raw[N1][N2];

        for (int i=0; i<N1; ++i) {
            for (int j=0; j<N2; ++j) {
                dataSet_raw[i][j] = mathFunc_f(x1_start + i*x1_step, x2_start + j*x2_step);
            }
        }

        dataSet.write(dataSet_raw, datatype);
    }

    /* Set metadata. (actually, just a small data sets) */
    {
        hsize_t dim[] = {1};
        H5::DataSpace dataSpace(1, dim);

        const std::array<const char *, 4> metaDataNames({"x1_start", "x1_step", "x2_start", "x2_step"});
        const std::array<const float *, 4> metaDataPtrs({&x1_start, &x1_step, &x2_start, &x2_step});

        for (size_t i=0; i<metaDataNames.size(); ++i) {
            H5::DataSet dataSet(group_metaData.createDataSet(metaDataNames[i], datatype, dataSpace));
            dataSet.write(metaDataPtrs[i], datatype);
        }
    }

    printf("File creation is done.\n");
    return EXIT_SUCCESS;
}

/**
 * @brief sinc function.
 *
 * @tparam T the data type of input
 * @param[in] x input value
 * @return sinc(x): sin(x)/x for |x| >= 0.001, 1 for |x| < 0.001
 */
template<typename T>
T sinc(const T x) {
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type.");
    if (std::abs(x) < 0.001) {
        return 1.0f;
    }
    return std::sin(x) / x;
}

/**
 * @brief sinc(sqrt(x1^2+x2^2))
 *
 * @tparam T the data type of input
 * @param x1 x1
 * @param x2 x2
 * @return sinc(sqrt(x1^2+x2^2))
 */
template<typename T>
T mathFunc_f(const T x1, const T x2) {
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type.");
    return sinc(std::sqrt(x1*x1 + x2*x2));
}
