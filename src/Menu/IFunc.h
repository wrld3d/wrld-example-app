// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace Eegeo
{
    namespace Helpers
    {
        template <typename TReturnType>
        class IFunc0
        {
        public:
            virtual ~IFunc0() {};
            virtual TReturnType operator()() const = 0;
        };

        template <typename TFuncContext, typename TReturnType>
        class TFunc0 : public IFunc0<TReturnType>
        {
        public:
            typedef TReturnType (TFuncContext::*TCallTarget)();

            TFunc0(TFuncContext* context, TCallTarget callback)
                : m_func(callback)
                , m_pContext(context)
            {
            }

            virtual ~TFunc0() { };

            virtual TReturnType operator()() const
            {
                return (*m_pContext.*m_func)();
            }
        private:
            TCallTarget m_func;
            TFuncContext* m_pContext;
        };

        template <typename TReturnType, typename TArg>
        class IFunc1
        {
        public:
            virtual ~IFunc1() { };
            virtual TReturnType operator()(TArg& arg) const = 0;
        };

        template <typename TFuncContext, typename TReturnType, typename TArg>
        class TFunc1 : public IFunc1<TReturnType, TArg>
        {
        public:
            typedef TReturnType (TFuncContext::*TCallTarget)(TArg& arg);

            TFunc1(TFuncContext* context, TCallTarget callback)
                : m_func(callback)
                , m_pContext(context)
            {
            }

            virtual ~TFunc1() { };

            virtual TReturnType operator()(TArg& arg) const
            {
                return (*m_pContext.*m_func)(arg);
            }
        private:
            TCallTarget m_func;
            TFuncContext* m_pContext;
        };

        template <typename TReturnType, typename TArg1, typename TArg2>
        class IFunc2
        {
        public:
            virtual ~IFunc2() { };
            virtual TReturnType operator()(TArg1& arg1, TArg2& arg2) const = 0;
        };

        template <typename TFuncContext, typename TReturnType, typename TArg1, typename TArg2>
        class TFunc2 : public IFunc2<TReturnType, TArg1, TArg2>
        {
        public:
            typedef TReturnType (TFuncContext::*TCallTarget)(TArg1& arg1, TArg2& arg2);

            TFunc2(TFuncContext* context, TCallTarget callback)
                : m_func(callback)
                , m_pContext(context)
            {
            }

            virtual ~TFunc2() { };

            virtual TReturnType operator()(TArg1& arg1, TArg2& arg2) const
            {
                return (*m_pContext.*m_func)(arg1, arg2);
            }
        private:
            TCallTarget m_func;
            TFuncContext* m_pContext;
        };
    }
}
