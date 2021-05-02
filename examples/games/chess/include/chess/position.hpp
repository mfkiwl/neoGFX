﻿/*
neogfx C++ App/Game Engine - Examples - Games - Chess
Copyright(C) 2020 Leigh Johnston

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <ostream>

#include <neolib/core/static_vector.hpp>

#include <chess/chess.hpp>
#include <chess/piece.hpp>
#include <chess/player.hpp>

namespace chess
{
    typedef neogfx::point_u32 coordinates;
    typedef coordinates::coordinate_type coordinate;

    typedef neogfx::point_i32 coordinates_i32;
    typedef coordinates_i32::coordinate_type coordinate_i32;

    struct move
    {
        coordinates from;
        coordinates to;
        std::optional<piece> promoteTo;
        piece capture = piece::None;
        enum class castling_piece_index : uint32_t
        {
            QueensRook  = 0x0,
            King        = 0x1,
            KingsRook   = 0x2,

            COUNT
        };
        typedef std::array<std::array<bool, static_cast<std::size_t>(castling_piece_index::COUNT)>, PIECE_COLORS> castling_state;
        castling_state castlingState;
    };

    inline bool operator==(move const& lhs, move const& rhs)
    {
        // todo: consider castling state?
        return lhs.from == rhs.from && lhs.to == rhs.to && lhs.promoteTo == rhs.promoteTo;
    }

    inline bool operator!=(move const& lhs, move const& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::string to_string(move const& aMove)
    {
        return { static_cast<char>('a' + aMove.from.x), static_cast<char>('1' + aMove.from.y), static_cast<char>('a' + aMove.to.x), static_cast<char>('1' + aMove.to.y) };
    }

    template <typename chess::player Player>
    inline coordinate promotion_rank_v;

    template <>
    inline coordinate promotion_rank_v<chess::player::White> = 7u;

    template <>
    inline coordinate promotion_rank_v<chess::player::Black> = 0u;

    typedef std::array<std::array<piece, 8>, 8> mailbox_rep;
    
    typedef uint64_t bitboard;

    struct bitboard_rep
    {
        std::array<bitboard, PIECE_COLORS> byColor;
        std::array<bitboard, PIECES> byPiece;
        std::array<piece, 64u> bySquare;
    };

    inline piece piece_at(mailbox_rep const& aRep, coordinates const& aCoordinates)
    {
        return aRep[aCoordinates.y][aCoordinates.x];
    }

    inline piece piece_at(bitboard_rep const& aRep, coordinates const& aCoordinates)
    {
        return aRep.bySquare[aCoordinates.y * 8u + aCoordinates.x];
    }
        
    inline void set_piece(mailbox_rep& aRep, coordinates const& aCoordinates, piece aPiece)
    {
        aRep[aCoordinates.y][aCoordinates.x] = aPiece;
    }

    inline void set_piece(bitboard_rep& aRep, coordinates const& aCoordinates, piece aPiece)
    {
        uint64_t const index = aCoordinates.y * 8u + aCoordinates.x;
        auto const oldPiece = aRep.bySquare[index];
        aRep.bySquare[index] = aPiece;
        if (aPiece == piece::None)
        {
            aRep.byColor[as_color_cardinal(piece::White)] &= ~index;
            aRep.byColor[as_color_cardinal(piece::Black)] &= ~index;
            aRep.byPiece[as_cardinal(oldPiece)] &= ~index;
        }
        else
        {
            aRep.byColor[as_color_cardinal(aPiece)] |= index;
            aRep.byColor[as_color_cardinal(piece_opponent_color(aPiece))] &= ~index;
            if (oldPiece != piece::None)
                aRep.byPiece[as_cardinal(oldPiece)] &= ~index;
            aRep.byPiece[as_cardinal(aPiece)] |= index;
        }
    }

    template <typename Representation>
    struct basic_position
    {
        Representation rep;
        std::array<coordinates, PIECE_COLORS> kings;
        player turn;
        std::vector<move> moveHistory;
        mutable std::optional<move> checkTest;
    };

    using mailbox_position = basic_position<mailbox_rep>;
    using bitboard_position = basic_position<bitboard_rep>;

    template <typename Representation>
    inline bool operator==(basic_position<Representation> const& lhs, basic_position<Representation> const& rhs)
    {
        bool const samePosition = lhs.rep == rhs.rep;
        bool const sameKings = lhs.kings == rhs.kings;
        bool const sameTurn = lhs.turn == rhs.turn;
        bool const sameHistory = lhs.moveHistory == rhs.moveHistory;
        return samePosition && sameKings && sameTurn && sameHistory;
    }

    template <typename Representation>
    inline bool operator!=(basic_position<Representation> const& lhs, basic_position<Representation> const& rhs)
    {
        return !(lhs == rhs);
    }

    using position = mailbox_position;

    inline constexpr coordinates coordinates_from_bit(bitboard aBits)
    {
        return coordinates{ static_cast<uint32_t>(aBits % 8ull), static_cast<uint32_t>(aBits / 8ull) };
    }

    inline constexpr bitboard bit_from_coordinates(coordinates const& aPosition)
    {
        return aPosition.x + aPosition.y * 8ull;
    }

    inline std::string to_string(piece aPiece, std::string const& aNone = ".")
    {
        switch (aPiece)
        {
        case piece::WhitePawn:
            return "P";
        case piece::WhiteKnight:
            return "N";
        case piece::WhiteBishop:
            return "B";
        case piece::WhiteRook:
            return "R";
        case piece::WhiteQueen:
            return "Q";
        case piece::WhiteKing:
            return "K";
        case piece::BlackPawn:
            return "p";
        case piece::BlackKnight:
            return "n";
        case piece::BlackBishop:
            return "b";
        case piece::BlackRook:
            return "r";
        case piece::BlackQueen:
            return "q";
        case piece::BlackKing:
            return "k";
        default:
            return aNone;
        }
    }

    template <typename CharT, typename CharTraitsT>
    inline std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& aStream, mailbox_position const& aPosition)
    {
        aStream << "  01234567" << std::endl << std::endl;
        for (coordinate y = 7u; y >= 0u && y <= 7u; --y)
        {
            aStream << y << " ";
            for (coordinate x = 0u; x <= 7u; ++x)
                aStream << to_string(aPosition.rep[y][x]);
            aStream << " " << y << std::endl;
        }
        aStream << std::endl << "  01234567" << std::endl;
        return aStream;
    }

    template <typename CharT, typename CharTraitsT>
    inline std::basic_ostream<CharT, CharTraitsT>& operator<<(std::basic_ostream<CharT, CharTraitsT>& aStream, bitboard_position const& aPosition)
    {
        aStream << "  01234567" << std::endl << std::endl;
        for (coordinate y = 7u; y >= 0u && y <= 7u; --y)
        {
            aStream << y << " ";
            for (coordinate x = 0u; x <= 7u; ++x)
                aStream << to_string(aPosition.rep.bySquare[x + y * 8u]);
            aStream << " " << y << std::endl;
        }
        aStream << std::endl << "  01234567" << std::endl;
        return aStream;
    }

    inline std::optional<move> undo(mailbox_position& aPosition)
    {
        std::optional<move> lastMove;
        if (!aPosition.moveHistory.empty())
        {
            lastMove = aPosition.moveHistory.back();
            auto const& lastMoveFrom = lastMove->from;
            auto const& lastMoveTo = lastMove->to;
            aPosition.moveHistory.pop_back();
            auto const movedPiece = piece_at(aPosition.rep, lastMoveTo);
            set_piece(aPosition.rep, lastMoveFrom, movedPiece);
            set_piece(aPosition.rep, lastMoveTo, lastMove->capture);
            if (lastMove->promoteTo)
            {
                // pawn promotion
                if (lastMove->to.y == promotion_rank_v<player::White>)
                    set_piece(aPosition.rep, lastMoveFrom, piece::WhitePawn);
                else if (lastMove->to.y == promotion_rank_v<player::Black>)
                    set_piece(aPosition.rep, lastMoveFrom, piece::BlackPawn);
            }
            else
            {
                switch (movedPiece)
                {
                case piece::BlackPawn:
                    // en passant (white)
                    if (lastMove->capture == piece::WhitePawn && lastMove->to == coordinates{ aPosition.moveHistory.back().to.x, 2u } &&
                        aPosition.moveHistory.back().to == coordinates{ aPosition.moveHistory.back().to.x, 3u } &&
                        aPosition.moveHistory.back().from == coordinates{ aPosition.moveHistory.back().to.x, 1u })
                    {
                        set_piece(aPosition.rep, lastMoveTo, piece::None);
                        set_piece(aPosition.rep, lastMoveTo.with_y(lastMoveTo.y + 1u), piece::WhitePawn);
                    }
                    break;
                case piece::WhitePawn:
                    // en passant (black)
                    if (lastMove->capture == piece::BlackPawn && lastMove->to == coordinates{ aPosition.moveHistory.back().to.x, 5u } &&
                        aPosition.moveHistory.back().to == coordinates{ aPosition.moveHistory.back().to.x, 4u } &&
                        aPosition.moveHistory.back().from == coordinates{ aPosition.moveHistory.back().to.x, 6u })
                    {
                        set_piece(aPosition.rep, lastMoveTo, piece::None);
                        set_piece(aPosition.rep, lastMoveTo.with_y(lastMoveTo.y - 1u), piece::BlackPawn);
                    }
                    break;
                case piece::WhiteKing:
                    aPosition.kings[as_color_cardinal<>(piece::WhiteKing)] = lastMoveFrom;
                    // castling (white)
                    if (lastMoveTo.x - lastMoveFrom.x == 2u)
                    {
                        set_piece(aPosition.rep, coordinates{ 7u, 0u }, piece::WhiteRook);
                        set_piece(aPosition.rep, coordinates{ 5u, 0u }, piece::None);
                    }
                    else if (lastMoveFrom.x - lastMoveTo.x == 2u)
                    {
                        set_piece(aPosition.rep, coordinates{ 0u, 0u }, piece::WhiteRook);
                        set_piece(aPosition.rep, coordinates{ 3u, 0u }, piece::None);
                    }
                    break;
                case piece::BlackKing:
                    aPosition.kings[as_color_cardinal<>(piece::BlackKing)] = lastMoveFrom;
                    // castling (black)
                    if (lastMoveTo.x - lastMoveFrom.x == 2u)
                    {
                        set_piece(aPosition.rep, coordinates{ 7u, 7u }, piece::BlackRook);
                        set_piece(aPosition.rep, coordinates{ 5u, 7u }, piece::None);
                    }
                    else if (lastMoveFrom.x - lastMoveTo.x == 2u)
                    {
                        set_piece(aPosition.rep, coordinates{ 0u, 7u }, piece::BlackRook);
                        set_piece(aPosition.rep, coordinates{ 3u, 7u }, piece::None);
                    }
                    break;
                default:
                    // do nothing
                    break;
                }
            }
            aPosition.turn = next_player(aPosition.turn);
        }
        return lastMove;
    }

    inline std::optional<move> undo(bitboard_position& aPosition)
    {
        // todo
        return {};
    }

    template <typename Representation>
    struct move_tables;
    template <typename Representation>
    move_tables<Representation> generate_move_tables();

    inline piece piece_at(mailbox_position const& aPosition, coordinates const& aCoordinates)
    {
        auto const targetPiece = aPosition.rep[aCoordinates.y][aCoordinates.x];
        if (!aPosition.checkTest)
            return targetPiece;
        if (aCoordinates == aPosition.checkTest->from)
            return piece::None;
        auto const movingPiece = !aPosition.checkTest->promoteTo ? aPosition.rep[aPosition.checkTest->from.y][aPosition.checkTest->from.x] : *aPosition.checkTest->promoteTo;
        // en passant
        if (piece_type(targetPiece) == piece::Pawn && piece_type(movingPiece) == piece::Pawn &&
            piece_color(targetPiece) != piece_color(movingPiece))
        {
            if (aPosition.checkTest->from.x != aPosition.checkTest->to.x)
            {
                if (!aPosition.moveHistory.empty() && aCoordinates == aPosition.moveHistory.back().to)
                {
                    if (std::abs(static_cast<int32_t>(aPosition.moveHistory.back().from.y) - static_cast<int32_t>(aPosition.moveHistory.back().to.y)) == 2)
                    {
                        if (aPosition.checkTest->to == coordinates{ aPosition.moveHistory.back().to.x, piece_color(movingPiece) == piece::White ? aPosition.moveHistory.back().to.y + 1 : aPosition.moveHistory.back().to.y - 1 })
                        {
                            return piece::None;
                        }
                    }
                }
            }
        }
        if (aCoordinates == aPosition.checkTest->to)
            return movingPiece;
        return targetPiece;
    }

    inline piece piece_at(bitboard_position const& aPosition, coordinates const& aCoordinates)
    {
        // todo
        return piece::None;
    }

    template <typename Representation>
    inline coordinates king_position(basic_position<Representation> const& aPosition, piece aKing)
    {
        auto const kingPosition = aPosition.kings[as_color_cardinal<>(aKing)];
        if (aPosition.checkTest && aPosition.checkTest->from == kingPosition)
            return aPosition.checkTest->to;
        return kingPosition;
    }

    template <typename Representation>
    inline bool draw(basic_position<Representation> const& aPosition)
    {
        // todo: hash board positions? could be slow.
        auto const moveCount = aPosition.moveHistory.size();
        return moveCount >= 6 &&
            aPosition.moveHistory[moveCount - 1] == aPosition.moveHistory[moveCount - 3] &&
            aPosition.moveHistory[moveCount - 1] == aPosition.moveHistory[moveCount - 5] &&
            aPosition.moveHistory[moveCount - 2] == aPosition.moveHistory[moveCount - 4] &&
            aPosition.moveHistory[moveCount - 2] == aPosition.moveHistory[moveCount - 6];
    }

    inline void move_piece(mailbox_position& aPosition, chess::move const& aMove)
    {
        auto& source = aPosition.rep[aMove.from.y][aMove.from.x];
        auto const movingPiece = source;
        auto& destination = aPosition.rep[aMove.to.y][aMove.to.x];
        auto const targetPiece = destination;
        destination = (!aMove.promoteTo ? source : *aMove.promoteTo);
        source = piece::None;
        auto const currentMoveCount = aPosition.moveHistory.size();
        aPosition.moveHistory.emplace_back(aMove.from, aMove.to, aMove.promoteTo, targetPiece, currentMoveCount > 0 ? aPosition.moveHistory[currentMoveCount - 1u].castlingState : move::castling_state{});
        auto& newMove = aPosition.moveHistory.back();
        switch (movingPiece)
        {
        case piece::WhiteKing:
        case piece::BlackKing:
            aPosition.kings[as_color_cardinal<>(destination)] = aMove.to;
            newMove.castlingState[as_color_cardinal<>(movingPiece)][static_cast<std::size_t>(move::castling_piece_index::King)] = true;
            if (aMove.from.x - aMove.to.x == 2)
            {
                // queenside castling
                newMove.castlingState[as_color_cardinal<>(movingPiece)][static_cast<std::size_t>(move::castling_piece_index::QueensRook)] = true;
                aPosition.rep[aMove.from.y][0u] = piece::None;
                aPosition.rep[aMove.from.y][3u] = piece_color(movingPiece) | piece::Rook;
            }
            else if (aMove.to.x - aMove.from.x == 2)
            {
                // kingside castling
                newMove.castlingState[as_color_cardinal<>(movingPiece)][static_cast<std::size_t>(move::castling_piece_index::KingsRook)] = true;
                aPosition.rep[aMove.from.y][7u] = piece::None;
                aPosition.rep[aMove.from.y][5u] = piece_color(movingPiece) | piece::Rook;
            }
            break;
        case piece::WhiteRook:
            if (aMove.from == coordinates{ 0u, 0u })
                newMove.castlingState[as_color_cardinal<>(piece::White)][static_cast<std::size_t>(move::castling_piece_index::QueensRook)] = true;
            else if (aMove.from == coordinates{ 7u, 0u })
                newMove.castlingState[as_color_cardinal<>(piece::White)][static_cast<std::size_t>(move::castling_piece_index::KingsRook)] = true;
            break;
        case piece::BlackRook:
            if (aMove.from == coordinates{ 0u, 7u })
                newMove.castlingState[as_color_cardinal<>(piece::Black)][static_cast<std::size_t>(move::castling_piece_index::QueensRook)] = true;
            else if (aMove.from == coordinates{ 7u, 7u })
                newMove.castlingState[as_color_cardinal<>(piece::Black)][static_cast<std::size_t>(move::castling_piece_index::KingsRook)] = true;
            break;
        case piece::WhitePawn:
            // en passant
            if (targetPiece == piece::None && aMove.from.x != aMove.to.x)
            {
                auto& targetPawn = aPosition.rep[4u][aMove.to.x];
                newMove.capture = targetPawn;
                targetPawn = piece::None;
            }
            break;
        case piece::BlackPawn:
            // en passant
            if (targetPiece == piece::None && aMove.from.x != aMove.to.x)
            {
                auto& targetPawn = aPosition.rep[3u][aMove.to.x];
                newMove.capture = targetPawn;
                targetPawn = piece::None;
            }
            break;
        default:
            // do nothing
            break;
        }
        switch (targetPiece)
        {
        case piece::WhiteRook:
            if (aMove.to == coordinates{ 0u, 0u })
                newMove.castlingState[as_color_cardinal<>(piece::White)][static_cast<std::size_t>(move::castling_piece_index::QueensRook)] = true;
            else if (aMove.to == coordinates{ 7u, 0u })
                newMove.castlingState[as_color_cardinal<>(piece::White)][static_cast<std::size_t>(move::castling_piece_index::KingsRook)] = true;
            break;
        case piece::BlackRook:
            if (aMove.to == coordinates{ 0u, 7u })
                newMove.castlingState[as_color_cardinal<>(piece::Black)][static_cast<std::size_t>(move::castling_piece_index::QueensRook)] = true;
            else if (aMove.to == coordinates{ 7u, 7u })
                newMove.castlingState[as_color_cardinal<>(piece::Black)][static_cast<std::size_t>(move::castling_piece_index::KingsRook)] = true;
            break;
        default:
            // do nothing
            break;
        }
        aPosition.turn = next_player(aPosition.turn);
    }

    inline void move_piece(bitboard_position& aPosition, chess::move const& aMove)
    {
        // todo
    }

    struct invalid_uci_move : std::runtime_error { invalid_uci_move() : std::runtime_error{ "chess::invalid_uci_move" } {} };

    inline move parse_uci_move(std::string const& aMove)
    {
        if (aMove.size() != 4 && aMove.size() != 5)
            throw invalid_uci_move();
        if (aMove[0] < 'a' || aMove[0] > 'h'|| aMove[1] < '1' || aMove[1] > '8' || aMove[2] < 'a' || aMove[2] > 'h' || aMove[3] < '1' || aMove[3] > '8')
            throw invalid_uci_move();
        move result;
        result.from.x = aMove[0] - 'a';
        result.from.y = aMove[1] - '1';
        result.to.x = aMove[2] - 'a';
        result.to.y = aMove[3] - '1';
        if (aMove.size() == 5)
            result.promoteTo = parse_piece_character(aMove[4]);
        return result;
    }

    template <typename Representation>
    basic_position<Representation> const& setup_position();

    struct eval_info
    {
        double material = 0.0;
        double mobility = 0.0;
        double attack = 0.0;
        double defend = 0.0;
        bool mobilityPlayer = false;
        bool mobilityOpponent = false;
        bool mobilityPlayerKing = false;
        bool mobilityOpponentKing = false;
        double checkedPlayerKing = 0.0;
        double checkedOpponentKing = 0.0;
        double eval;
        std::chrono::microseconds time_usec;
    };

    enum class eval_node 
    {
        Branch      = 0,
        Terminal    = 1
    };

    struct eval_result
    {
        eval_node node;
        double eval;
    };

    template <typename Representation, player Player>
    struct eval
    {
        eval_result operator()(move_tables<Representation> const& aTables, basic_position<Representation> const& aPosition, double aPly, eval_info* aEvalInfo = nullptr);
        eval_result operator()(move_tables<Representation> const& aTables, basic_position<Representation> const& aPosition, double aPly, eval_info& aEvalInfo);
    };
}