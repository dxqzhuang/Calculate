#ifndef TERM_ERROR_H
#define TERM_ERROR_H

namespace  termErr {
    enum ERR
    {
        BAD_FORMAT   //when somethign is neither an TermExpr nor a TermVal,
                     //then it's in the wrong format.
    };
}



#endif // TERM_ERROR_H
