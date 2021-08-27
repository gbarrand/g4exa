// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef AIDA_IFUNCTIONCATALOG_H
#define AIDA_IFUNCTIONCATALOG_H 1

//  This file is part of the AIDA library
//  Copyright (C) 2002 by the AIDA team.  All rights reserved.
//  This library is free software and under the terms of the
//  GNU Library General Public License described in the LGPL.txt 

#include <string>
#include <vector>

namespace AIDA {

class IFunction;

/** @interface 
 *
 * Function catalog.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */
 
class IFunctionCatalog {

public: 
    /// Destructor.
    virtual ~IFunctionCatalog() { /* nop */; }

    /**
     * Remember persistently definition (code!) of a function under a name.
     * Scripted function created by the user may be automatically available
     * in the subsequent analysis sessions. This is also a way to create
     * new names for combinations of exisiting model functions ("G+G+E+P5").
     * Last but not least, system may be easily extended with model functions
     * developed in the programming language directly.
     * Predefined functions: "G","E","Pn".
     */
    virtual bool add(std::string nameId, IFunction * f) = 0;

    virtual bool add(std::string nameId, const std::string & codelet) = 0;

    /*
     * Get a list of all available functions.
     */
    virtual std::vector<std::string>  list() = 0;

    /*
     * Remove function from the catalog.
     */
    virtual void remove(const std::string & nameId) = 0;

    /*
     * Write contents of the catalog to disk.
     * We have to agree on the format here, or define and XML 
     * entry for IFunctionCatalog!
     */
    virtual bool storeAll(const std::string & nameOnDisk) = 0;

    /* 
     * Load contents of the catalog from disk
     * We have to agree on the format here, or define and XML 
     * entry for IFunctionCatalog!
     */
    virtual bool loadAll(const std::string & nameOnDisk) = 0;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFUNCTIONCATALOG_H */