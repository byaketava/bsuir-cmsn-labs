BEGIN;

CREATE TYPE club_conference AS ENUM ('восток', 'запад');
CREATE TYPE player_position AS ENUM ('вратарь', 'защитник', 'нападающий');
CREATE TYPE player_grip AS ENUM ('L', 'R');
CREATE TYPE match_finish_type AS ENUM ('основное время', 'овертайм', 'послематчевые буллиты');
CREATE TYPE match_status AS ENUM ('ожидается', 'идёт', 'завершён', 'отменён');
CREATE TYPE club_match_role AS ENUM ('хозяева', 'гости');
CREATE TYPE club_match_result AS ENUM ('победа', 'поражение');
CREATE TYPE referee_role AS ENUM ('главный', 'линейный');

-- Таблица club
CREATE TABLE IF NOT EXISTS public.club (
    id INTEGER PRIMARY KEY,
    "name" VARCHAR(255) NOT NULL,
    city VARCHAR(255) NOT NULL,
    foundation_year INTEGER NOT NULL CHECK (foundation_year > 1875),
    conference club_conference NOT NULL
);
COMMENT ON TABLE public.club IS 'Клубы';
COMMENT ON COLUMN public.club."name" IS 'Название клуба';
COMMENT ON COLUMN public.club.city IS 'Город, в котором базируется клуб';
COMMENT ON COLUMN public.club.foundation_year IS 'Год основания клуба';
COMMENT ON COLUMN public.club.conference IS 'Конференция, в которой играет клуб';

-- Таблица player
CREATE TABLE IF NOT EXISTS public.player (
    id INTEGER PRIMARY KEY,
    "name" VARCHAR(255) NOT NULL,
    age INTEGER NOT NULL CHECK (age >= 17),
    country VARCHAR(255) NOT NULL,
    "number" INTEGER NOT NULL CHECK ("number" >= 1 AND "number" <= 99),
    "position" player_position NOT NULL,
	grip player_grip NOT NULL,
    points INTEGER DEFAULT 0 CHECK (points >= 0),
    club_id INTEGER,
    CONSTRAINT player_club_id_fkey FOREIGN KEY (club_id)
        REFERENCES public.club (id)
        ON UPDATE CASCADE
        ON DELETE SET NULL
);
COMMENT ON TABLE public.player IS 'Игроки хоккейных команд';
COMMENT ON COLUMN public.player."name" IS 'ФИО игрока';
COMMENT ON COLUMN public.player.age IS 'Возраст игрока';
COMMENT ON COLUMN public.player.country IS 'Гражданство игрока';
COMMENT ON COLUMN public.player."number" IS 'Игровой номер игрока';
COMMENT ON COLUMN public.player."position" IS 'Амплуа игрока';
COMMENT ON COLUMN public.player.grip IS 'Хват игрока';
COMMENT ON COLUMN public.player.points IS 'Очки, набранные игроком за сезон';

-- Таблица arena
CREATE TABLE IF NOT EXISTS public.arena (
    id INTEGER PRIMARY KEY,
    "name" VARCHAR(255) NOT NULL,
    city VARCHAR(255) NOT NULL,
    construction_year INTEGER NOT NULL CHECK (construction_year > 1800),
    capacity INTEGER NOT NULL CHECK (capacity > 0),
    club_id INTEGER UNIQUE,
    CONSTRAINT arena_club_id_fkey FOREIGN KEY (club_id)
        REFERENCES public.club (id)
        ON UPDATE CASCADE
        ON DELETE SET NULL
);
COMMENT ON TABLE public.arena IS 'Арены, на которых проводятся хоккейные матчи';
COMMENT ON COLUMN public.arena."name" IS 'Название арены';
COMMENT ON COLUMN public.arena.city IS 'Город расположения арены';
COMMENT ON COLUMN public.arena.construction_year IS 'Год постройки арены';
COMMENT ON COLUMN public.arena.capacity IS 'Вместимость арены';

-- Таблица match
CREATE TABLE IF NOT EXISTS public.match (
    id INTEGER PRIMARY KEY,
    "date" DATE NOT NULL,
    finish_type match_finish_type DEFAULT NULL,
	score VARCHAR(10) NOT NULL CHECK (score::TEXT ~ '^[0-9]+-[0-9]+$'),
    status match_status NOT NULL,
    arena_id INTEGER,
    CONSTRAINT match_arena_id_fkey FOREIGN KEY (arena_id)
        REFERENCES public.arena (id)
        ON UPDATE CASCADE
        ON DELETE SET NULL
);
COMMENT ON TABLE public.match IS 'Матчи, проводящиеся в рамках чемпионата';
COMMENT ON COLUMN public.match.score IS 'Счет матча в формате X-Y';
COMMENT ON COLUMN public.match."date" IS 'Дата проведения матча';
COMMENT ON COLUMN public.match.finish_type IS 'Тип завершения (основное время, овертайм, послематчевые буллиты)';
COMMENT ON COLUMN public.match.status IS 'Статус матча (завершен, идет, ожидается, отменен)';

-- Таблица club_match
CREATE TABLE IF NOT EXISTS public.club_match (
    club_id INTEGER NOT NULL,
    match_id INTEGER NOT NULL,
    "role" club_match_role NOT NULL,
    "result" club_match_result NOT NULL,
    PRIMARY KEY (club_id, match_id),
    CONSTRAINT club_match_club_id_fkey FOREIGN KEY (club_id)
        REFERENCES public.club (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT club_match_match_id_fkey FOREIGN KEY (match_id)
        REFERENCES public.match (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);
COMMENT ON TABLE public.club_match IS 'Связь между клубами и матчами';
COMMENT ON COLUMN public.club_match."role" IS 'Роль команды в матче';
COMMENT ON COLUMN public.club_match."result" IS 'Результат команды в матче';

-- Таблица referee
CREATE TABLE IF NOT EXISTS public.referee (
    id INTEGER PRIMARY KEY,
    "name" VARCHAR(255) NOT NULL,
    "number" INTEGER  NOT NULL CHECK ("number" >= 1 AND "number" <= 99) UNIQUE,
    age INTEGER NOT NULL CHECK (age >= 18 AND age <= 65),
    "role" referee_role NOT NULL
);
COMMENT ON TABLE public.referee IS 'Арбитры хоккейных матчей';
COMMENT ON COLUMN public.referee."name" IS 'ФИО арбитра';
COMMENT ON COLUMN public.referee."number" IS 'Номер арбитра';
COMMENT ON COLUMN public.referee.age IS 'Возраст арбитра';
COMMENT ON COLUMN public.referee."role" IS 'Амплуа арбитра';

-- Таблица match_referee
CREATE TABLE IF NOT EXISTS public.match_referee (
    match_id INTEGER NOT NULL,
    referee_id INTEGER NOT NULL,
    PRIMARY KEY (match_id, referee_id),
    CONSTRAINT match_referee_match_id_fkey FOREIGN KEY (match_id)
        REFERENCES public.match (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT match_referee_referee_id_fkey FOREIGN KEY (referee_id)
        REFERENCES public.referee (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);
COMMENT ON TABLE public.match_referee IS 'Связь между матчами и арбитрами';

-- Таблица player_match
CREATE TABLE IF NOT EXISTS public.player_match (
    player_id INTEGER NOT NULL,
    match_id INTEGER NOT NULL,
    goals INTEGER DEFAULT 0 CHECK (goals >= 0),
    assists INTEGER DEFAULT 0 CHECK (assists >= 0),
    penalties INTEGER DEFAULT 0 CHECK (penalties >= 0),
    PRIMARY KEY (player_id, match_id),
    CONSTRAINT player_match_player_id_fkey FOREIGN KEY (player_id)
        REFERENCES public.player (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT player_match_match_id_fkey FOREIGN KEY (match_id)
        REFERENCES public.match (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);
COMMENT ON TABLE public.player_match IS 'Связь между игроками и матчами';
COMMENT ON COLUMN public.player_match.goals IS 'Количество голов, забитых игроком в данном матче';
COMMENT ON COLUMN public.player_match.assists IS 'Количество результативных передач, выполненных игроком в данном матче';
COMMENT ON COLUMN public.player_match.penalties IS 'Количество штрафов, заработанных игроком данном матче';

-- Таблица coach
CREATE TABLE IF NOT EXISTS public.coach (
    id INTEGER PRIMARY KEY,
    "name" VARCHAR(255) NOT NULL,
    age INTEGER NOT NULL CHECK (age >= 18 AND age <= 99),
    country VARCHAR(255) NOT NULL,
    games_count INTEGER DEFAULT 0 CHECK (games_count >= 0),
    club_id INTEGER,
    CONSTRAINT coach_club_id_fkey FOREIGN KEY (club_id)
        REFERENCES public.club (id)
        ON UPDATE CASCADE
        ON DELETE SET NULL
);
COMMENT ON TABLE public.coach IS 'Тренеры хоккейных клубов';
COMMENT ON COLUMN public.coach."name" IS 'ФИО тренера';
COMMENT ON COLUMN public.coach.age IS 'Возраст тренера';
COMMENT ON COLUMN public.coach.country IS 'Гражданство тренера';
COMMENT ON COLUMN public.coach.games_count IS 'Количество игр в качестве тренера в лиге';

-- Таблица club_statistics
CREATE TABLE IF NOT EXISTS public.club_statistics (
    id INTEGER PRIMARY KEY,
    games INTEGER DEFAULT 0 CHECK (games >= 0),
    wins INTEGER DEFAULT 0 CHECK (wins >= 0),
    ot_wins INTEGER DEFAULT 0 CHECK (ot_wins >= 0),
    pb_wins INTEGER DEFAULT 0 CHECK (pb_wins >= 0),
    goals VARCHAR(255) DEFAULT '0-0' CHECK (goals ~ '^[0-9]+-[0-9]+$'),
    points INTEGER DEFAULT 0 CHECK (points >= 0),
    club_id INTEGER UNIQUE,
    CONSTRAINT club_statistics_club_id_fkey FOREIGN KEY (club_id)
        REFERENCES public.club (id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);
COMMENT ON TABLE public.club_statistics IS 'Статистика клубов';
COMMENT ON COLUMN public.club_statistics.games IS 'Количество сыгранных клубом игр';
COMMENT ON COLUMN public.club_statistics.wins IS 'Количество выигрышей в основное время';
COMMENT ON COLUMN public.club_statistics.ot_wins IS 'Количество выигрышей в овертайме';
COMMENT ON COLUMN public.club_statistics.pb_wins IS 'Количество выигрышей в послематчевых буллитах';
COMMENT ON COLUMN public.club_statistics.goals IS 'Количество забитых и пропущенных голов в формате X-Y';
COMMENT ON COLUMN public.club_statistics.points IS 'Количество очков, набранных клубом в текущем сезоне';

END;
