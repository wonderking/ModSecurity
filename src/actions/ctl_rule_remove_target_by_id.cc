/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#include "actions/ctl_rule_remove_target_by_id.h"

#include <iostream>
#include <string>
#include <vector>

#include "modsecurity/transaction.h"

namespace modsecurity {
namespace actions {

bool CtlRuleRemoveTargetById::init(std::string *error) {
    std::string what(m_parser_payload, 21, m_parser_payload.size() - 21);
    std::vector<std::string> param = split(what, ';');

    if (param.size() < 2) {
        error->assign(what + " is not a valid `ID;VARIABLE'");
        return false;
    }

    try {
        m_id = std::stoi(param[0]);
    } catch(...) {
        error->assign("Not able to convert '" + param[0] +
            "' into a number");
        return false;
    }

    m_target = param[1];

    return true;
}

bool CtlRuleRemoveTargetById::evaluate(Rule *rule, Transaction *transaction) {
    transaction->m_ruleRemoveTargetById.push_back(
        std::make_pair(m_id, m_target));
    return true;
}

}  // namespace actions
}  // namespace modsecurity
