#ifndef MATRIX_H
#define MATRIX_H

// #include <pybind11/pybind11.h>
// #include <pybind11/eigen.h>

namespace py = pybind11;

struct buffer_info{
    void *ptr;
    ssize_t itemsize;
    std::string format;
    ssize_t ndim;
    std::vector<ssize_t> shape;
    std::vector<ssize_t> strides;
};

class Matrix {
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
        m_data = new float[rows*cols];
    }
    float *data() {return m_data;}
    size_t rows() const {return m_rows;}
    size_t cols() const {return m_cols;}
    
private:
    size_t m_rows, m_cols;
    float *m_data;
};

py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
    .def_buff([](Matrix &m) -> py::buffer_info {
        return py::buffer_info(
            m.data(),
            sizeof(float),
            py::format_description<float>::format(),
            2,
            {m.rows(), m.cols()},
            {sizeof(float)*m.cols(),
             sizeof(float) }
         );
     });
     
typedef Eigen::MatrixXd Matrix;
typedef Matrix::Scalar Scalar;
constexpr bool rowMajor = Matrix::Flags & Eigen::RowMajorBit;

py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
    .def("__init__", [](Matrix &m, py::buffer b) {
        typedef Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic> Strides;
        
        /* Request a buffer descriptor from Python */
        py::buffer_info info = b.request();
        
        /* Sanity check */
        if (info.format != py::format_description<Scalar>::format())
            throw std::runtime_error("Incompatible format: expected a double array!");
            
        if (info.ndim != 2)
            throw std::runtime_error("Incompatible buffer dimension!");
            
        auto strides = Strides(
            info.strides[rowMajor ? 0 : 1] / py::ssize_t)sizeof(Scalar),
            info.strides[rowMajor ? 1 : 0] / py::ssize_t)sizeof(Scalar));
            
        auto map = Eigen::Map<Matrix, 0, Strides>(
            static_cast<Scalar *>(info.ptr), info.shape[0], info.shape[1], strides);
            
        new (&m) Matrix(map);
   });
            
       
#endif        
