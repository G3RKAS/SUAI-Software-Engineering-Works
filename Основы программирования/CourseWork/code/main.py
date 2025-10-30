from telegram import *
from telegram.ext import *
import tg_sql as sql
from warnings import filterwarnings
from telegram.warnings import PTBUserWarning
import json

filterwarnings(action="ignore", message=r".*CallbackQueryHandler", category=PTBUserWarning)

(
    SELECTING_ACTION,
    SETUP_DATA,
    EDITING,
    AGE,
    HEIGHT,
    WEIGHT,
    INFO,
    TRAINS,
    ADD_TRAIN,
    REMOVE_TRAIN,
    UPLOAD_TRAINS,
    SHOW_TRAINS_PAGE,
    PAGE,
    BACK_BASE,
    FORWARD_BASE,
    DELETE_EXACT_TRAIN,
    LOAD_EXACT_TRAIN,
    ADDIT_INFO,
    TYPING,
    PROFILE,
    PROFILE_EDITING,
    PERSONAL_PLAN,
    SHOW_BASE,
    SELF_TRAINS_MENU,
    DELETE_TRAINS,
    SHOW_TRAINS,
    AUTHOR,
    TO_FEEDBACK,
    FEEDBACK,
    TO_MENU,
    BACK,
    STOP,
) = map(chr, range(32))

app = ApplicationBuilder().token("TG TOKEN").build()

def find_train_by_number(number, data):
    i = 1
    for item in data:
        if i == number:
            return item
        i += 1

def setup_user_data(update, context):
    user_data = context.user_data
    if update.callback_query:
        data = sql.get_data_from_users(update.callback_query.from_user.id)
    else:
        data = sql.get_data_from_users(update.message.from_user.id)
    user_data[INFO] = {AGE: str(data['age']), WEIGHT: str(data['weight']), HEIGHT: str(data['height'])}

    if data['add_info'] is None or not(data['add_info'] and data['add_info'].strip()):
        user_data[INFO][ADDIT_INFO] = "Отсутсвует"
    else:
        user_data[INFO][ADDIT_INFO] = data['add_info']

    if data['trains'] == '[]' or data['trains'] is None:
        user_data[INFO][TRAINS] = list()
    else:
        trains = json.loads(data['trains'])
        user_data[INFO][TRAINS] = trains

    user_data[INFO][UPLOAD_TRAINS] = {'Status':0}
    user_data[INFO][PAGE] = 1

async def start(update, context):
    user_id = update.message.from_user.id

    text = "Привет, добро пожаловать в бота, позволяющего создать план индивидуальной тренировки!"
    await update.message.reply_text(text=text)

    if not sql.is_user_in_users(user_id):
        context.user_data[INFO] = {AGE: 'None', HEIGHT: 'None', WEIGHT: 'None'}
        context.user_data[EDITING] = ''
        return await menu_of_data(update, context, "Вам необходимо заполнить данные профиля: ")
    else:
        setup_user_data(update, context)
        context.user_data[BACK] = False
        if not sql.is_user_profile_full(user_id):
            context.user_data[EDITING] = ''
            return await menu_of_data(update, context, "Вам необходимо дополнить данные профиля: ")
        else:
            context.user_data[EDITING] = None
            return await menu(update, context)

async def menu_of_data(update, context, text="Выберите пункт редактирования"):
    user_data = context.user_data
    text = text
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_menu.jpg'
    media = InputMediaPhoto(media=media_photo,  caption=text)

    buttons = [
        [
            InlineKeyboardButton(text="Рост", callback_data=str(HEIGHT)),
            InlineKeyboardButton(text="Вес", callback_data=str(WEIGHT)),
        ],
        [
            InlineKeyboardButton(text="Возраст", callback_data=str(AGE)),
        ],
    ]

    if user_data[INFO][AGE] != 'None' and user_data[INFO][HEIGHT] != 'None' and user_data[INFO][WEIGHT] != 'None':
        setup_user_data(update, context)
        buttons.append([InlineKeyboardButton(text="В меню", callback_data=str(TO_MENU))],)

    keyboard = InlineKeyboardMarkup(buttons)

    if user_data[EDITING] is None:
        await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=keyboard
        )

    user_data[BACK] = True

    return SETUP_DATA

async def editing(update, context):
    user_data = context.user_data
    if update.callback_query:
        user_data[EDITING] = update.callback_query.data

    button = [[InlineKeyboardButton(text="Назад", callback_data=str(TO_MENU))]]
    text = ""
    if user_data[EDITING] == AGE:
        text = "Введите информацию о возрасте: "
    elif user_data[EDITING] == HEIGHT:
        text = "Введите информацию о росте: "
    elif user_data[EDITING] == WEIGHT:
        text = "Введите информацию о весе: "
    elif user_data[EDITING] == ADDIT_INFO:
        text = "Введите желаемую заметку: "
    elif user_data[EDITING] == ADD_TRAIN:
        button.append([InlineKeyboardButton(text="Выбрать из базы", switch_inline_query_current_chat="")])
        text = "Введите текст пункта: \n\n"
        text += "*Вы можете предложить добавить в базу тренировку\n"
        text += "*Об авторе -> Обратная связь\n"
    elif user_data[EDITING] == REMOVE_TRAIN:
        text = "Введите номер пункта: \n\n"
        i = 1
        for item in user_data[INFO][TRAINS]:
            text += str(i) + ". " + item +  "\n"
            i += 1
    elif user_data[EDITING] == UPLOAD_TRAINS:
        stat = user_data[INFO][UPLOAD_TRAINS]
        if stat['Status'] == 1:
            text = "Введите имя вашего плана: "
        elif stat['Status'] == 2:
            text = "Введите описание вашего плана: "
    elif user_data[EDITING] == DELETE_TRAINS or user_data[EDITING] == SHOW_TRAINS:
        text = "Введите номер плана: \n\n"
        i = 1
        for item in user_data[INFO][SHOW_TRAINS_PAGE]:
            name = ''
            if user_data[INFO][SHOW_TRAINS]['status'] == 'base':
                name += " от "
                try:
                    profile_user = await context.bot.get_chat(item['tg_id'])
                    name += profile_user.first_name.capitalize()
                except:
                    name += "Неизвестно"
            text += str(i) + ". " + item['train_name'] + name + "\n"
            i += 1
    reply = InlineKeyboardMarkup(button)

    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_menu.jpg'
    media = InputMediaPhoto(media=media_photo, caption=text)
    if update.callback_query:
        await update.callback_query.edit_message_media(media=media, reply_markup=reply)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=reply
        )

    return TYPING

async def save_info(update, context):
    user_data = context.user_data
    user_data_edit = user_data[EDITING]
    user_text = update.message.text
    user_id = update.message.from_user.id

    if user_data_edit == AGE or user_data_edit == WEIGHT or user_data_edit == HEIGHT or user_data_edit == REMOVE_TRAIN or user_data_edit == DELETE_TRAINS or user_data[EDITING] == SHOW_TRAINS:
        if not(user_text.isnumeric()):
            text = "Некоректные данные!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
        else:
            user_text = int(user_text)

    if user_data_edit == AGE:
        if user_text <= 0 or user_text > 120:
            text = "Некоректные данные!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == WEIGHT:
        if user_text <= 20 or user_text > 500:
            text = "Некоректные данные!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == HEIGHT:
        if user_text <= 70 or user_text > 255:
            text = "Некоректные данные!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == ADDIT_INFO or user_data_edit == ADD_TRAIN:
        if len(user_text) >=150:
            text = "Текст слишком длинный!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == REMOVE_TRAIN:
        if int(user_text) > len(user_data[INFO][TRAINS]) or int(user_text) < 1:
            text = "Такого пункта не существует!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == UPLOAD_TRAINS:
        if user_data[INFO][UPLOAD_TRAINS]['Status'] == 1:
            if sql.is_user_train_in_bd_by_name(user_id, user_text):
                text = "У вас уже есть план с таким именем!\nПовторите попытку: "
                await update.message.reply_text(text=text)
                return TYPING
        if len(user_text) >= 150:
            text = "Текст слишком длинный!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING
    elif user_data_edit == DELETE_TRAINS or user_data[EDITING] == SHOW_TRAINS:
        if not find_train_by_number(int(user_text), user_data[INFO][SHOW_TRAINS_PAGE]) or int(user_text) < 1:
            text = "Такого пункта не существует!\nПовторите попытку: "
            await update.message.reply_text(text=text)
            return TYPING


    if user_data_edit == ADD_TRAIN:
        user_data[INFO][TRAINS].append(str(user_text))
    elif user_data_edit == REMOVE_TRAIN:
        user_data[INFO][TRAINS].pop(user_text - 1)
    elif user_data_edit == UPLOAD_TRAINS:
        stat = user_data[INFO][UPLOAD_TRAINS]
        if stat['Status'] == 1:
            stat['Name'] = str(user_text)
            stat['Status'] = 2
            return await editing(update, context)
        elif stat['Status'] == 2:
            stat['Descp'] = str(user_text)
    elif user_data_edit == DELETE_TRAINS:
        user_data[INFO][DELETE_TRAINS] = find_train_by_number(int(user_text), user_data[INFO][SHOW_TRAINS_PAGE])['train_name']
    elif user_data[EDITING] == SHOW_TRAINS:
        user_data[INFO][SHOW_TRAINS]['train'] = find_train_by_number(int(user_text), user_data[INFO][SHOW_TRAINS_PAGE])
    else:
        user_data[INFO][user_data_edit] = str(user_text)
    saving(update, context)

    if user_data_edit == ADDIT_INFO or user_data_edit == ADD_TRAIN or user_data_edit == REMOVE_TRAIN:
        user_data[BACK] = False
        return await show_plan(update, context)
    elif user_data_edit == UPLOAD_TRAINS or user_data_edit == DELETE_TRAINS:
        user_data[BACK] = False
        return await self_trains_menu(update, context)
    elif user_data[EDITING] == SHOW_TRAINS:
        return await show_exact_trains(update, context)


    return await menu_of_data(update, context, "Продолжаем заполнение: ")

def saving(update, context):
    user_data = context.user_data
    user_id = update.message.from_user.id


    if user_data[EDITING] == AGE:
        sql.set_user_age(user_id, user_data[INFO][AGE])
    elif user_data[EDITING] == WEIGHT:
        sql.set_user_weight(user_id, user_data[INFO][WEIGHT])
    elif user_data[EDITING] == HEIGHT:
        sql.set_user_height(user_id, user_data[INFO][HEIGHT])
    elif user_data[EDITING] == ADD_TRAIN or user_data[EDITING] == REMOVE_TRAIN:
        sql.set_user_trains(user_id, json.dumps(user_data[INFO][TRAINS], ensure_ascii=False))
    elif user_data[EDITING] == ADDIT_INFO:
        sql.set_user_info(user_id, user_data[INFO][ADDIT_INFO])
    elif user_data[EDITING] == UPLOAD_TRAINS and user_data[INFO][UPLOAD_TRAINS]['Status'] == 2:
        sql.upload_user_train(user_id, user_data[INFO][UPLOAD_TRAINS]['Name'], sql.get_data_from_users(user_id)['trains'], user_data[INFO][UPLOAD_TRAINS]['Descp'])
        user_data[INFO][UPLOAD_TRAINS]['Status'] = 0
    elif user_data[EDITING] == DELETE_TRAINS:
        sql.delete_user_train_by_name(user_id, user_data[INFO][DELETE_TRAINS])


async def menu(update, context):
    context.user_data[INFO][SHOW_TRAINS_PAGE] = list()
    context.user_data[INFO][PAGE] = 1
    context.user_data[EDITING] = None

    text = "Вы можете выбрать своё дальнейшее действие: "
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_menu.jpg'
    media = InputMediaPhoto(media=media_photo,  caption=text)

    buttons = [
        [
            #InlineKeyboardButton(text="Напоминания", callback_data=str(REMINDERS)),
            InlineKeyboardButton(text="План тренировок", callback_data=str(PERSONAL_PLAN)),
        ],
        [
            InlineKeyboardButton(text="База готовых планов", callback_data=str(SHOW_BASE)),
        ],
        [
            InlineKeyboardButton(text="Профиль", callback_data=str(PROFILE)),
        ],
        [
            InlineKeyboardButton(text="Об авторе", callback_data=str(AUTHOR)),
        ]
    ]
    keyboard = InlineKeyboardMarkup(buttons)

    if context.user_data[BACK]:
        await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=keyboard
        )

    context.user_data[BACK] = True
    return SELECTING_ACTION

async def author(update, context):
    text = "Автор : G3RKA \nДизайнер: SickoSasha\nСпонсор: The Frokich \nВерсия: beta v1"
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_author.png'
    media = InputMediaPhoto(media=media_photo,  caption=text)

    buttons = [
        [InlineKeyboardButton(text="Обратная связь", callback_data=str(TO_FEEDBACK))],
        [InlineKeyboardButton(text="Назад", callback_data=str(TO_MENU))]
    ]
    keyboard = InlineKeyboardMarkup(buttons)

    await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)

    context.user_data[BACK] = True

    return SELECTING_ACTION

async def feedback(update, context):
    text = "Добро пожаловать в обратную связь!\nВведите сообщение, которое вы хотите отправить автору."
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_feedback.png'
    media = InputMediaPhoto(media=media_photo,  caption=text)

    await update.callback_query.edit_message_media(media=media)

    context.user_data[BACK] = False

    return FEEDBACK

async def send_feed(update, context):
    text = update.message.text
    print("Отправлено сообщение по обратной связи:\n", text)

    text = "Получено новое сообщение по обратной связи от @" + update.message.from_user.username + ':\n'+ text
    await context.bot.send_message(text=text,chat_id=605787598)

    return await menu(update, context)

async def profile(update, context):
    user_data = context.user_data

    text = "Профиль " + update.callback_query.from_user.username
    media_photo = await update.callback_query.from_user.get_profile_photos()
    media_photo = media_photo.photos[0][0].file_id

    buttons = [
        [InlineKeyboardButton(text="Редактировать", callback_data=str(PROFILE_EDITING))],
        [InlineKeyboardButton(text="Назад", callback_data=str(TO_MENU))]
    ]
    keyboard = InlineKeyboardMarkup(buttons)

    text += "\nВозраст: " + user_data[INFO][AGE]
    text += "\nРост: " + user_data[INFO][HEIGHT]
    text += "\nВес: " + user_data[INFO][WEIGHT]

    media = InputMediaPhoto(media=media_photo, caption=text)

    await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)

    context.user_data[BACK] = True

    return SELECTING_ACTION

async def base_train(update, context):
    user_data = context.user_data
    if update.callback_query:
        if update.callback_query.data == FORWARD_BASE:
            user_data[BACK] = True
            user_data[INFO][PAGE] += 1
        elif update.callback_query.data == BACK_BASE:
            user_data[BACK] = True
            user_data[INFO][PAGE] -= 1

    page = user_data[INFO][PAGE]
    user_data[INFO][SHOW_TRAINS_PAGE] = list()
    user_data[INFO][SHOW_TRAINS] = {'status': 'base'}
    text = "Открытая база планов тренировок от других пользователей.\n\n"
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_base.jpg'

    data = sql.get_all_users_trains_by_page()
    data_to_show = data[(10 * (page-1)):(10 * page)]

    text += "Список планов:\n\n"
    if len(data_to_show) == 0:
        text += "Отсутствует\n"
    else:
        i = 1
        for item in data_to_show:
            try:
                profile_user = await context.bot.get_chat(item['tg_id'])
                name = profile_user.first_name.capitalize()
            except:
                name = "Неизвестно"
            user_data[INFO][SHOW_TRAINS_PAGE].append(item)
            text += str(i) + ". " + item['train_name'] + " от " + name + "\n"
            i += 1
            text += "\n"

    move_buttons = list()
    if page > 1:
        move_buttons.append(InlineKeyboardButton(text="Назад", callback_data=str(BACK_BASE)))
    if len(data) - (10*page) > 0:
        move_buttons.append(InlineKeyboardButton(text="Вперёд", callback_data=str(FORWARD_BASE)))

    upload_buttons = [InlineKeyboardButton(text="Мои планы", callback_data=str(SELF_TRAINS_MENU))]

    buttons = [
        move_buttons,
        upload_buttons,
        [(InlineKeyboardButton(text="Просмотреть пункт", callback_data=str(SHOW_TRAINS)))],
        [InlineKeyboardButton(text="В меню", callback_data=str(TO_MENU))]
    ]

    keyboard = InlineKeyboardMarkup(buttons)

    media = InputMediaPhoto(media=media_photo, caption=text)

    if context.user_data[BACK]:
        await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=keyboard
        )

    context.user_data[BACK] = True

    return SELECTING_ACTION

async def self_trains_menu(update, context):
    if update.callback_query:
        user_id = update.callback_query.from_user.id
    else:
        user_id = update.message.from_user.id
    user_data = context.user_data
    user_data[INFO][SHOW_TRAINS] = {'status': 'self'}
    text = "Список опубликованных вами планов.\n\n"
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_base.jpg'

    user_data[INFO][SHOW_TRAINS_PAGE] = list()
    adding_buttons = list()
    show_buttons = list()
    if len(sql.get_all_user_train(user_id)) < 10:
        adding_buttons.append(InlineKeyboardButton(text="Загрузить текущий план", callback_data=str(UPLOAD_TRAINS)))
    if len(sql.get_all_user_train(user_id)) > 0:
        adding_buttons.append(InlineKeyboardButton(text="Удалить план", callback_data=str(DELETE_TRAINS)))
        show_buttons = [(InlineKeyboardButton(text="Просмотреть пункт", callback_data=str(SHOW_TRAINS)))]

    buttons = [
        adding_buttons,
        show_buttons,
        [InlineKeyboardButton(text="В меню", callback_data=str(TO_MENU))],
    ]

    keyboard = InlineKeyboardMarkup(buttons)

    text += "Список планов:\n\n"
    if len(sql.get_all_user_train(user_id)) == 0:
        text += "Отсутсвует\n"
    else:
        i = 1
        for item in sql.get_all_user_train(user_id):
            user_data[INFO][SHOW_TRAINS_PAGE].append(item)
            text += str(i) + ". " + item['train_name'] +  "\n"
            i += 1

    text += "\n"

    text += "Лимит общего количества планов: 10\n"


    media = InputMediaPhoto(media=media_photo, caption=text)

    if context.user_data[BACK]:
        await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=keyboard
        )

    context.user_data[BACK] = True
    return SELECTING_ACTION

async def show_exact_trains(update, context):
    user_data = context.user_data
    text = "Информация о плане тренировки.\n\n"
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_base.jpg'
    buttons = list()

    train = user_data[INFO][SHOW_TRAINS]['train']

    try:
        profile_user = await context.bot.get_chat(train['tg_id'])
        name = profile_user.first_name.capitalize()
    except:
        name = "Неизвестно"

    text += "Имя: " + train["train_name"] + "\n"

    text += "Описание: " + train["descp"] + "\n"

    text += "План: " + "\n"
    i = 1
    for item in json.loads(train["trains"]):
        text += str(i) + ". " + item + "\n"
        i += 1
    text += "\n"
    text += "Создатель: " + name

    text += "\n\n"

    if int(train['tg_id']) == update.message.from_user.id:
        buttons.append([InlineKeyboardButton(text="Удалить план", callback_data=str(DELETE_EXACT_TRAIN))])

    text += "*При загрузке плана Ваш текущий план исчезнет!"
    buttons.append([InlineKeyboardButton(text="Загрузить план себе", callback_data=str(LOAD_EXACT_TRAIN))])
    buttons.append([InlineKeyboardButton(text="В меню", callback_data=str(TO_MENU))])


    keyboard = InlineKeyboardMarkup(buttons)

    await update.message.reply_photo(
        photo=media_photo,
        caption=text,
        reply_markup=keyboard
    )

    context.user_data[BACK] = True
    return SELECTING_ACTION

async def delete_exact_train(update, context):

    user_data = context.user_data
    user_id = update.callback_query.from_user.id

    train = user_data[INFO][SHOW_TRAINS]['train']

    sql.delete_user_train_by_name(user_id, train['train_name'])

    context.user_data[BACK] = True
    if user_data[INFO][SHOW_TRAINS]['status'] == 'self':
        return await self_trains_menu(update, context)
    elif user_data[INFO][SHOW_TRAINS]['status'] == 'base':
        return await base_train(update, context)

async def load_exact_train(update, context):
    user_data = context.user_data
    user_id = update.callback_query.from_user.id
    train = user_data[INFO][SHOW_TRAINS]['train']
    trains = json.loads(train['trains'])

    user_data[INFO][TRAINS] = trains
    sql.set_user_trains(user_id, json.dumps(user_data[INFO][TRAINS], ensure_ascii=False))

    user_data[BACK] = True
    return await show_plan(update, context)


async def show_plan(update, context):
    user_data = context.user_data

    text = "Ваш личный план тренировок: \n\n"
    media_photo = 'http://a1048263.xsph.ru/wp-content/uploads/2024/11/image_plan.jpg'

    adding_buttons = list()

    if len(user_data[INFO][TRAINS]) <= 15:
        adding_buttons.append(InlineKeyboardButton(text="Добавить пункт плана", callback_data=str(ADD_TRAIN)))
    if len(user_data[INFO][TRAINS]) > 0:
        adding_buttons.append(InlineKeyboardButton(text="Удалить пункт плана", callback_data=str(REMOVE_TRAIN)))

    buttons = [
        adding_buttons,
        [InlineKeyboardButton(text="Редактировать заметку", callback_data=str(ADDIT_INFO))],
        [InlineKeyboardButton(text="Назад", callback_data=str(TO_MENU))]
    ]
    keyboard = InlineKeyboardMarkup(buttons)

    text += "Список упражнений:\n"
    if len(user_data[INFO][TRAINS]) == 0:
        text += "Отсутсвует\n"
    else:
        i = 1
        for item in user_data[INFO][TRAINS]:
            text += str(i) + ". " + item + "\n"
            i += 1

    text += "\n"

    text += "Личная заметка:\n"
    text += user_data[INFO][ADDIT_INFO]+ "\n\n"

    text += "*Максимум пунктов: 15\n"

    media = InputMediaPhoto(media=media_photo, caption=text)

    if context.user_data[BACK]:
        await update.callback_query.edit_message_media(media=media, reply_markup=keyboard)
    else:
        await update.message.reply_photo(
            photo=media_photo,
            caption=text,
            reply_markup=keyboard
        )

    context.user_data[BACK] = True

    return SELECTING_ACTION

async def upload_trains(update, context):
    user_data = context.user_data
    user_data[INFO][UPLOAD_TRAINS]['Status'] = 1
    return await editing(update, context)

async def stop(update, context):
    text = "ОШИБКА. ТЫ НЕ ДОЛЖЕН ЗДЕСЬ НАХОДИТЬСЯ"
    media_photo = 'https://media.discordapp.net/attachments/406507556954177548/1296119098568212572/image.png?ex=671860b9&is=67170f39&hm=1cf365ab667e6b1cbf5e910393b5c7cb60ec81be691aebdff693c44da75ca8dc&format=webp&quality=lossless&width=364&height=350&'
    media = InputMediaPhoto(media=media_photo, caption=text)
    await update.callback_query.edit_message_media(media=media)

    return STOP

async def inline_query_res(update, context):
    query = update.inline_query.query

    data = sql.get_all_trains()
    results = list()

    i = 1
    for item in data:
        training = item['trains']
        if str(query).lower() in training.lower() or len(query.strip()) == 0:
            results.append(InlineQueryResultArticle(
                id=str(i),
                title=training,
                input_message_content=InputTextMessageContent(training),
            ))
            i += 1
        else:
            continue

    await update.inline_query.answer(results)

def main():

    selection_handlers = [
        CallbackQueryHandler(profile, pattern="^" + str(PROFILE) + "$"),
        CallbackQueryHandler(author, pattern="^" + str(AUTHOR) + "$"),
        CallbackQueryHandler(feedback, pattern="^" + str(TO_FEEDBACK) + "$"),
        CallbackQueryHandler(base_train, pattern="^" + str(SHOW_BASE) + "$|^" + str(FORWARD_BASE) + "$|^" + str(BACK_BASE) + "$"),
        CallbackQueryHandler(self_trains_menu, pattern="^" + str(SELF_TRAINS_MENU) + "$"),
        CallbackQueryHandler(show_plan, pattern="^" + str(PERSONAL_PLAN) + "$"),
        CallbackQueryHandler(upload_trains, pattern="^" + str(UPLOAD_TRAINS) + "$"),
        CallbackQueryHandler(delete_exact_train, pattern="^" + str(DELETE_EXACT_TRAIN) + "$"),
        CallbackQueryHandler(load_exact_train, pattern="^" + str(LOAD_EXACT_TRAIN) + "$"),
        CallbackQueryHandler(editing, pattern="^" + str(ADDIT_INFO) + "$|^"+ str(ADD_TRAIN)+ "$|^" + str(REMOVE_TRAIN) + "$|^" + str(DELETE_TRAINS) + "$|^" + str(SHOW_TRAINS) + "$"),
        CallbackQueryHandler(menu_of_data, pattern="^" + str(PROFILE_EDITING) + "$"),
        CallbackQueryHandler(menu, pattern="^" + str(TO_MENU) + "$"),
    ]

    selection_data = [
        CallbackQueryHandler(editing, pattern="^" + str(AGE) + "$|^" + str(HEIGHT)+ "$|^" + str(WEIGHT) + "$"),
        CallbackQueryHandler(menu, pattern="^" + str(TO_MENU) + "$"),
    ]

    conv_handler = ConversationHandler(
        entry_points=[CommandHandler("start", start)],
        states={
            FEEDBACK: [MessageHandler(filters=filters.TEXT & ~filters.COMMAND, callback=send_feed)],
            TYPING: [
                CallbackQueryHandler(menu, pattern="^" + str(TO_MENU) + "$"),
                MessageHandler(filters=filters.TEXT & ~filters.COMMAND, callback=save_info)
            ],
            SELECTING_ACTION: selection_handlers,
            SETUP_DATA: selection_data,
            STOP: [CommandHandler("start", start)],
        },
        fallbacks=[
            CallbackQueryHandler(stop),
        ],
        allow_reentry = True,
    )

    app.add_handler(conv_handler)
    app.add_handler(InlineQueryHandler(inline_query_res), 1)

    if not sql.check_server():
        print("ОШИБКА: БАЗА НЕ ПОДКЛЮЧЕНА")
        print("Остановка.")
        app.stop_running()
    else:
        print("Бот успешно запушен!")
        app.run_polling()

if __name__ == "__main__":
    main()