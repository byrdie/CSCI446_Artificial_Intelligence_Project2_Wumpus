#include "knowledge.h"

theta Knowledge::unification(pred x, pred y, theta sub_list) {

    pred_args x_args = get<1>(x);
    pred_args y_args = get<1>(y);


    /* Check that the same predicates are used and the same number of arguments are used. */
    if ((get<0>(x) != get<0>(y)) || (x_args.size() != y_args.size())) {
        return sub_list;
    }

    /* loop through all the arguments of each predicate and unify */
    for (uint i = 0; i < x_args.size(); i++) {
        sub_list = unify_var(x_args[i], y_args[i], sub_list);
        if (sub_list.empty()) {
            return sub_list;
        }
    }
    return sub_list;
}

theta Knowledge::unify_var(func x, func y, theta sub_list) {

    theta empty_list;

    /* Check if x or y is already in the sublist */
    for (uint i = 0; i < sub_list.size(); i++) {

        func tfunc = sub_list[i][0];
        func sfunc = sub_list[i][1];

        /* Check to see if we already have a substitution for this variable */
        if (func_eq(x, tfunc)) { // Full function substitution
            x = sfunc;
        }
        if (func_eq(y, tfunc)) { // Full function substitution
            y = sfunc;
        }
    }

    int xname = get<0>(x);
    int yname = get<0>(y);


    /* Attempt unification if no substitution has been provided for x or y */
    if (func_eq(x, y)) { // If x == y then we're done

        sub_list = sub_var(x, y, sub_list);

        return sub_list;

    } 
//    else if (xname == F_CONST and yname != F_CONST) {
//
//        sub_list = sub_const(x, y, sub_list);
//
//    } 
//    else if (yname == F_CONST and xname != F_CONST) {
//
//        sub_list = sub_const(y, x, sub_list);
//
//    } 
    else if (xname == F_VAR) { // x is a variable; y is variable or function

        sub_list = sub_var(x, y, sub_list);

    } else if (yname == F_VAR) { // y is a variable; x is a function

        sub_list = sub_var(y, x, sub_list);

    } else if (xname >= F_NORTH and yname >= F_NORTH) { // x and y are both functions

        /* x and y must be the same function to be unified */
        if (xname == yname) {

            func_args xargs = get<1>(x);
            func_args yargs = get<1>(y);

            vector<vector < uint>> arg_sub;

            /* Assume that x and y have the same number of arguments (since they're supposedly the same function) */
            for (uint i = 0; i < xargs.size(); i++) {

                /* Select a single argument of x and y */
                uint u = xargs[i];
                uint v = yargs[i];

                /* Convert the arguments u and v to functions for later */
                func_args ua;
                func_args va;
                ua.push_back(u);
                va.push_back(v);
                func uf = build_func(F_VAR, ua);
                func vf = build_func(F_VAR, va);

                /* Check if u or v is already in the sublist */
                for (uint i = 0; i < sub_list.size(); i++) {

                    func tfunc = sub_list[i][0];
                    func sfunc = sub_list[i][1];

                    /* Check to see if we already have a substitution for these variables */
                    if (func_eq(uf, tfunc)) { // Full function substitution
                        u = get<1>(sfunc)[0]; // update u
                        if (get<0>(sfunc) >= F_NORTH) { // unification fails, we cannot nest functions
                            return empty_list;
                        }
                    }
                    if (func_eq(vf, tfunc)) { // Full function substitution
                        v = get<1>(sfunc)[0]; // update v
                        if (get<0>(sfunc) >= F_NORTH) { // unification fails, we cannot nest functions
                            return empty_list;
                        }
                    }

                }
                arg_sub = unify_arg(u, v, arg_sub); // Unify arguments
            }

            /* translate integer array into function array and push onto sub list */
            for (uint i = 0; i < arg_sub.size(); i++) { // Loop over substitution

                /* Add substitution */
                vector<func> fargsub;

                func subvar;
                func subval;

                if ((arg_sub[i][0] & A_CONST) > 0) {
                    subvar = build_fconst(arg_sub[i][0]);
                } else {
                    subvar = build_fvar(arg_sub[i][0]);
                }

                if ((arg_sub[i][1] & A_CONST) > 0) {
                    subval = build_fconst(arg_sub[i][1]);
                } else {
                    subval = build_fvar(arg_sub[i][1]);
                }

                fargsub.push_back(subvar);
                fargsub.push_back(subval);
                sub_list.push_back(fargsub);

                /* Add back-substitution */
                //                vector<func> back_fargsub;
                //                back_fargsub.push_back(subval);
                //                back_fargsub.push_back(subvar);
                //                sub_list.push_back(back_fargsub);
            }

        } else { // Unification fails

            return empty_list;
        }
    } else {// Unification fails


        return empty_list;
    }
    return sub_list;

}

vector<vector<uint>> Knowledge::unify_arg(uint x, uint y, vector<vector<uint>> sub_list) {

    //check if x or y are already in the the sublist
    for (uint i = 0; i < sub_list.size(); i++) {
        if (x == sub_list[i][0]) {
            x = sub_list[i][1];
        }
        if (y == sub_list[i][0]) {
            y = sub_list[i][1];
        }
    }
    if (x == y) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);

    } else if ((x & A_CONST) == 0) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);

    } else if ((y & A_CONST) == 0) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(y);
        s_sub_list.push_back(x);
        sub_list.push_back(s_sub_list);

    } else {
        vector<vector < uint>> list;
        return list;
    }
    return sub_list;
}

/**
 * 
 * @param x assumed to be a variable!!!!
 * @param y
 * @return 
 */
theta Knowledge::sub_var(func x, func y, theta sub_list) {

    /* add the substitution */
    vector<func> subsub_list;
    subsub_list.push_back(x);
    subsub_list.push_back(y);
    sub_list.push_back(subsub_list);

    /* add opposite rule */
    //    vector<func> subsub_list2;
    //    subsub_list2.push_back(y);
    //    subsub_list2.push_back(x);
    //    sub_list.push_back(subsub_list2);

    /* if y is a constant, add the inverse of the substitution */
    //            if (get<0>(y) == F_CONST) {
    //                vector<func> back_sub;
    //                int inverse = func_inv[get<0>(y)];
    //                if (inverse != 0) { // inverse exists
    //                    get<0>(x) = inverse;
    //                    get<0>(y) = F_VAR;
    //                    back_sub.push_back(y);
    //                    back_sub.push_back(x);
    //                    sub_list.push_back(back_sub);
    //                } else {
    //                    cout << "Attempting to invert non-invertible function" << endl;
    //        
    //                    theta empty_list;
    //                    return empty_list;
    //                }
    //            }
    return sub_list;
}

theta Knowledge::sub_const(func x, func y, theta sub_list) {

    vector<func> back_sub;
    int inverse = func_inv[get<0>(y)];
    if (inverse != 0) { // inverse exists
        get<0>(x) = inverse;
        get<0>(y) = F_VAR;
        back_sub.push_back(y);
        back_sub.push_back(x);
        sub_list.push_back(back_sub);
    } else {
        cout << "Attempting to invert non-invertible function" << endl;

        theta empty_list;
        return empty_list;
    }

    return sub_list;

}