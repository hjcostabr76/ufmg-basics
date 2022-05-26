#ifndef TRASHRECYCLING_ENUMS_H
#define TRASHRECYCLING_ENUMS_H

/**
 * ENUM
 * Define tipos de usuario do sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
enum PersonTypeEnum {
    PF = 100,
    PJ = 101
};


/**
 * ENUM
 * Define tipos de actions de Controllers do sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
enum ControllerActionEnum {
    DEFAULT = 110,
    CREATE = 111,
    RETRIVE = 112,
    UPDATE = 113,
    DELETE = 114
};

/**
 * ENUM
 * Define tipos de usuario do sistema
 * Trash Recycling System
 *
 * @author hjcostabr
 */
enum UserTypeEnum {
    ADMIN = 120,
    DONATOR = 121,
    RECEIVER = 122
};

#endif //TRASHRECYCLING_ENUMS_H
